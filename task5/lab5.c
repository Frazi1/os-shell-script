#define FUSE_USE_VERSION 30
#define _FILE_OFFSET_BITS 64

#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

struct node;

typedef enum node_type {
	FILE,
	DIRECTORY
} node_type;

typedef struct file_node {
	int size;
	char *data;
} file_node_t;

typedef struct dir_node {
	struct node *first_child;
} dir_node_t;

typedef struct node {
	char *name;
	struct node *next_sibling;
	node_type type;
	mode_t mode;
	int links_count;

	union {
		file_node_t file;
		dir_node_t dir;
	} content;

} node_t;

static node_t *root;

static node_t *findNode(const char *path, node_t *parent) {
	int entry_len = 0;
	node_t *current, *result = NULL;

	while (*path != '\0' && *path == '/') {
		path++;
	}

	while (path[entry_len] != '\0' &&
		path[entry_len] != '/') {
		entry_len++;
	}

	if (parent == NULL || parent->type != DIRECTORY) {
		result = parent;
	}
	else if (entry_len == 0) {
		result = parent;
	}
	else {
		current = parent->content.dir.first_child;
		while (current != NULL && strncmp(current->name, path, entry_len)) {
			current = current->next_sibling;
		}

		if (current != NULL) {
			result = findNode(path + entry_len, current);
		}
	}

	return result;
}

static void add_child_node(node_t *parent, node_t *child) {
	child->next_sibling = parent->content.dir.first_child;
	parent->content.dir.first_child = child;
}

static node_t *create_directory(char *name) {
	node_t *node;

	node = (node_t *)malloc(sizeof(node_t));

	node->name = name;
	node->mode = 0777;
	node->type = DIRECTORY;
	node->next_sibling = NULL;
	node->content.dir.first_child = NULL;
	node->links_count = 2;

	return node;
}

static node_t *create_directory_and_append_to_parent(char *path, mode_t mode, node_t *parent) {
	node_t *d = create_directory(path);
	parent->links_count++;
	add_child_node(parent, d);
	return d;
}

static node_t *create_file(char *name) {
	node_t *node;

	node = (node_t *)malloc(sizeof(node_t));

	node->name = name;
	node->mode = 0666;
	node->type = FILE;
	node->next_sibling = NULL;
	node->content.file.size = 0;
	node->content.file.data = NULL;
	node->links_count = 0;

	return node;
}

static int copy_file(const char *path) {
	FILE* input, *output;
	char buffer[10];
	size_t nread;

	node_t* file = create_file("cat");
	input = fopen("/bin/cat", "rb");
	while (nread = fread(buffer, sizeof(char), sizeof(buffer), input)) {
		fwrite(buffer, sizeof(char), nread, file->content.file.data);
		file->content.file.size += nread;
	}
	file->links_count++;
	add_child_node(root, file);
}

static struct fuse_operations operations = {
	.getattr = getattr,
	.readdir = readdir,
	.read = read,
	.mkdir = mkdir,
	.chmod = chmod
};

static int getattr(const char *path, struct stat *st) {
	node_t *node;

	node = findNode(path, root);
	if (node != NULL) {
		st->st_mode = node->mode;
		if (node->type == DIRECTORY) {
			st->st_mode |= S_IFDIR;
		}
		else if (node->type == FILE) {
			st->st_mode |= S_IFREG;
			st->st_size = node->content.file.size;
		}

		//st->st_nlink = node->n_links;
		st->st_uid = getuid();
		st->st_gid = getgid();
	}
	else {
		return -ENOENT;
	}

	return 0;
}

static int readdir(const char *path,
	void *buffer,
	fuse_fill_dir_t filler,
	off_t offset,
	struct fuse_file_info *fi) {
	node_t *parent_node, *current_node;

	filler(buffer, ".", NULL, 0);
	filler(buffer, "..", NULL, 0);

	parent_node = findNode(path, root);

	if (parent_node != NULL) {

		current_node = parent_node->content.dir.first_child;
		while (current_node != NULL) {
			filler(buffer, current_node->name, NULL, 0);
			current_node = current_node->next_sibling;
		}
		return 0;
	}


	static int read(const char *path,
		char *buffer,
		size_t size,
		off_t offset,
		struct fuse_file_info *fi) {
		node_t *node;
		int bytes_read = 0;

		node = findNode(path, root);
		if (node != NULL && offset < node->content.file.size) {
			int bytes_available = node->content.file.size - offset;
			if (bytes_available >= size) {
				bytes_read = size;
			}
			else {
				bytes_read = bytes_available;
			}

			if (bytes_read > 0) {
				memcpy(buffer, node->content.file.data, bytes_read);
			}
		}

		return bytes_read;
	}


	static int chmod(const char *path, mode_t mode) {
		node_t *node = findNode(path, root);
		if (node != NULL) {
			node->mode = mode;
			return 0;
		}
		return -1;
	}

	static int mkdir(const char *path, mode_t mode) {

		int nameLen = 0;
		for (int i = strlen(path) - 1; i >= 0; i--) {
			if (path[i] == '/') break;
			nameLen++;
		}

		node_t *dir;

		if (nameLen != strlen(path) - 1) {
			char* pathToDir = (char*)malloc(strlen(path) - nameLen - 1);
			strncpy(pathToDir, path, strlen(path) - nameLen - 1);
			pathToDir[strlen(path) - nameLen - 1] = '\0';
			dir = findNode(pathToDir, root);
		}
		else {
			dir = root;
		}

		if (dir == NULL) return -1;

		char *corrected_path = (char *)malloc(nameLen);
		strncpy(corrected_path, path + strlen(path) - nameLen, nameLen);
		corrected_path[nameLen] = '\0';
		create_directory_and_append_to_parent(corrected_path, mode, dir);
		return 0;
	}


	static void init() {
		node_t *first, *second;
		node_t *file;
		node_t *first_inner;

		first = create_directory_and_append_to_parent("first", 0777, root);

		second = create_directory("second");
		root->links_count++; /* a new subfolder */
		add_child_node(root, second);

		first_inner = create_directory("first_inner");
		first->links_count++; /* a new subfolder */
		add_child_node(first, first_inner);
		file = create_file("sample.txt");
		file->links_count++; /* a new hard link */
		add_child_node(root, file);

		file->content.file.data = "Hello";
		file->content.file.size = strlen(file->content.file.data);

		node_t* script = create_file("script.sh");
		script->links_count++;
		add_child_node(root, script);
		script->content.file.data = "#!/bin/bash echo 123";
		script->content.file.size = strlen(script->content.file.data);
	}

	int main(int argc, char *argv[]) {
		root = create_directory("");
		init();
		return fuse_main(argc, argv, &operations, NULL);
	}
