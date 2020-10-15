#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "trie.h"

/*
  quick hack for debugging
  won't print any entry that is a subset of another
  so it prints terminating paths, not entries
  example: if can and canada are both entries, only canada will print
 */
void print_paths(const struct trie_node *const node, int pos) {
  static char prefix[256];
  char c = node->letter;
  if (node->down != NULL) {
    prefix[pos] = c;
    printf("%c", c);
    print_paths(node->down, pos + 1);
  }
  else {
    printf("%c\n", c);
  }
  if (node->next != NULL) {
    for (int i = 0; i < pos; i++) {
      printf("%c", prefix[i]);
    }
    print_paths(node->next, pos);
  }
}

/*
  visit every node
 */
void print_nodes(struct trie_node *node) {
  printf("%c", node->letter);
  if (node->down != NULL) {
    print_nodes(node->down);
  }
  if (node->next != NULL) {
    printf("\n");
    print_nodes(node->next);
  }
}

int main() {
  // TODO: write actual tests
  const char *cool = "cool";
  struct trie trie = {.root = NULL};
  trie_add_entry(&trie, "can", NULL);
  trie_add_entry(&trie, "canada", NULL);
  trie_add_entry(&trie, "canadian", NULL);
  trie_add_entry(&trie, "cool", (void *)cool);
  trie_add_entry(&trie, "cent", NULL);
  trie_add_entry(&trie, "cell", NULL);
  trie_add_entry(&trie, "ceiling", NULL);
  trie_add_entry(&trie, "cellar", NULL);
  trie_add_entry(&trie, "shell", NULL);
  trie_add_entry(&trie, "smell", NULL);
  trie_add_entry(&trie, "shoe", NULL);
  print_paths(trie.root, 0);
  struct trie_search_result search = trie_search(&trie, "coo");
  struct trie_node *bfs = trie_bfs(search.last->down);
  printf("should print cool: %s\n", (char *)bfs->data);
  trie_dealloc_nodes(&trie.root);
}
