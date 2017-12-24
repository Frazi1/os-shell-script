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

int f_getattr(const char* path, struct stat* st );

int f_readdir(const char * path,
              void * buffer,
              fuse_fill_dir_t filler,
              off_t offset,
              struct fuse_file_info * info) ;


typedef enum f_node_type {
    F_NODE_DIRECTORY,
    F_NODE_FILE
} f_node_type;

typedef struct f_node_dir {
    struct f_node* children;
} f_node_dir;

typedef struct f_node_file {
    off_t size;
    char* data;
} f_node_file;

typedef struct f_node {
    char* name;
    mode_t mode;
    nlink_t links;
    f_node_type type;
    struct f_node* next_sibling;
    union {
        struct f_node_dir dir;
        struct f_node_file file;
    } info;
} f_node;

//f_node* find_node(const char* path, f_node* parent) ;

f_node*find_node1(const char *path, f_node *parent)
;

int f_read(const char *path,
                   char *buffer,
                   size_t size,
                   off_t offset,
                   struct fuse_file_info *fi) ;

f_node* create_dir(char *path, mode_t mode, f_node* parent) ;

int f_mkdir(const char * path, mode_t mode);

f_node* root;

static struct fuse_operations operations = {
        .getattr = f_getattr,
        .readdir = f_readdir,
        .read    = f_read,
        .mkdir   = f_mkdir
};

int f_getattr(const char* path, struct stat* st ){
    printf("get attr %s\n", path);
    f_node* node = find_node1(path, root);
    if(node == NULL) {
        printf("not found\n");
        return -ENOENT;
    }
    st->st_mode = node->mode;
    if(node->type == F_NODE_DIRECTORY) {
        st->st_mode |= S_IFDIR;
    }
    if(node->type == F_NODE_FILE) {
        st->st_mode |= S_IFREG;
        st->st_size = node->info.file.size;
    }
    st->st_nlink = node->links;
    st->st_uid = getuid();
    st->st_gid = getgid();
    return 0;
}

int f_readdir(const char * path,
              void * buffer,
              fuse_fill_dir_t filler,
              off_t offset,
              struct fuse_file_info * info) {
    f_node *parent_node, *current_node;

    printf("do_readdir: %s\n", path);
    filler( buffer, ".", NULL, 0 );
    filler( buffer, "..", NULL, 0 );
    parent_node = find_node1(path, root);
    if(parent_node != NULL) {
        current_node = parent_node->info.dir.children;
        while(current_node != NULL) {
            filler(buffer, current_node->name, NULL, 0);
            current_node = current_node->next_sibling;
        }
    } else {
        printf("dir not found");
    }
    return 0;
}

 int f_read(const char *path,
                   char *buffer,
                   size_t size,
                   off_t offset,
                   struct fuse_file_info *fi) {
    printf("read");
     return 0;
}

int f_mkdir(const char * path, mode_t mode){
    printf("mkdir11111: %s\n", path);
    while(*path != "\0" && *path =="/") {
        path++;
    }

    create_dir(path, mode, root);
    return 0;
}

f_node* create_dir(char *path, mode_t mode, f_node* parent) {
    printf("create dir: %s\n",path);
    f_node* node = (f_node*) malloc(sizeof(f_node));
    node->name = path;
    node->links = 2;
    node->mode = mode;
    node->next_sibling = NULL;
    node->type = F_NODE_DIRECTORY;
    node->info.dir.children = NULL;

    if(parent != NULL) {
        if(parent->info.dir.children == NULL){
            parent->info.dir.children = node;
        } else {
          f_node* current_last = parent->info.dir.children;
            while (current_last->next_sibling != NULL){
                current_last = current_last->next_sibling;
            }
            current_last->next_sibling = node;
        }
    }
    return node;
}


//f_node* find_node(const char* path, f_node* parent) {
//    printf("find %s %p\n", path, parent);
//    f_node *current = NULL, *result = NULL;
//    while(*path != "\0" && *path == "/") {
//        path++;
//    }
//    int name_lenght = 0;
//    while(path[name_lenght] != "\0"
//          && path[name_lenght] != "/") {
//        name_lenght++;
//    }
//    if(name_lenght == 0){
//        return  parent;
//    } else {
//        current = parent->info.dir.children;
//        while (current != NULL) {
//            if (strncmp(current->name, path, (size_t) name_lenght)) {
//                printf("found %s\n");
//                break;
//            }
//            current = current->next_sibling;
//        }
//
//        if (current != NULL)
//        {
//            result = find_node(path + name_lenght, current);
//        }
//    }
//    printf("not found");
//    return result;
//}

f_node*find_node1(const char *path, f_node *parent)
{
    int entry_len = 0;
    f_node *current, *result = NULL;

    printf("find %s %p\n", path, parent);

    /* skip leading '/' symbols */
    while (*path != '\0' && *path == '/')
    {
        path++;
    }

    /* calculate the length of the current path entry */
    while (path[entry_len] != '\0' &&
           path[entry_len] != '/')
    {
        entry_len++;
    }

    if (parent == NULL || parent->type != F_NODE_DIRECTORY)
    {
        /* 'parent' must represent a directory */
        result = parent;
    }
    else if (entry_len == 0)
    {
        /* if the path is empty (e.g. "/" or ""), return parent */
        result = parent;
    }
    else
    {
        /* traverse children in search for the next entry */
        current = parent->info.dir.children;
        while (current != NULL && strncmp(current->name, path, entry_len))
        {
            current = current->next_sibling;
        }

        if (current != NULL)
        {
            result = find_node1(path + entry_len, current);
        }
    }

    return result;
}

int main(int argc, char *argv[]){
    root = create_dir("", 0666, NULL);
    return fuse_main(argc, argv, &operations, NULL);
}