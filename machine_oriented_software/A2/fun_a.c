#include <stdio.h>
#include <stdlib.h>


struct _sorted_list_ {
  struct _sorted_list_* next;
  struct _sorted_list_* prev;
  int data;  
};

typedef struct _sorted_list_ sorted_list;


sorted_list* sorted_list_create() {
/**
  * Creates the header element of the list and returns the pointer to it.
  */
  
  sorted_list* new_list = malloc(sizeof(sorted_list));

  if (new_list == NULL)
  {
    printf("Error allocating memory for a sorted list!\n");
    return NULL;
  }

  new_list->prev = NULL;
  new_list->next = NULL;
  return new_list;
}

void sorted_list_add(sorted_list** list, int data) {
/**
  * Adds an element at the right position to our sorted linked list.
  * 
  */  
  sorted_list* new_element = malloc(sizeof(sorted_list));

  if (new_element == NULL)
  {
    printf("Error allocating memory new element!\n");
    return;
  }

  sorted_list* index_element = *list;
  new_element->data = data;

  while(1)
  {
    if (index_element->prev == NULL)
    {
      // We're at the header element. Add the new element after it and change 
      // list pointer:
      new_element->prev = *list;
      new_element->next = NULL;
      index_element->next = new_element;
      (*list) = new_element;
      // Now the list pointer is pointing to the first
      // actual element of the list.
      return;
    }

    if (index_element->data >= new_element->data)
    {
      // We're at an element that is greater than or equal to our element.
      // We add the new element before the index element

      if (index_element->prev->prev == NULL)
      {
        // The element before the index element is the first element of the
        // list. We have to change the list pointer to make sure it's pointing
        // to the first element.
        (*list) = new_element;
      }

      new_element->next = index_element;
      new_element->prev = index_element->prev;
      index_element->prev->next = new_element;
      index_element->prev = new_element;
      return;
    }

    if (index_element->next == NULL)
    {
      // We're at the last list element. We need to add the new element
      // to the end of our list
      new_element->next = NULL;
      new_element->prev = index_element;
      index_element->next = new_element;
      return;
    }

    index_element = index_element->next;

  }

}

void sorted_list_destroy(sorted_list** list) {
/**
  * Destroys the the list and frees the memory.
  * 
  */
  
  sorted_list* current_element = (*list);
  sorted_list* next_element = (*list)->next;

  // If the list pointer points to the header element, this won't do
  // anything. If not, it will free the memory for the header element.
  free(current_element->prev); 

  while (current_element != NULL)
  {
    next_element = current_element->next;
    free(current_element);
    current_element = next_element;
  }

}

void sorted_list_remove(sorted_list** list, int index) {
/**
  * Removes an element from the linked list at a given index.
  * Nothing is done if the index is out of range.
  */

  sorted_list* index_element = *list;

  if (index_element->prev == NULL)
  {
    // We're at the header element. No element can be removed so we'll just
    // return.
    return;
  }


  for (int running_index = 0; running_index <= index; running_index++)
  {
    if (running_index == index)
    {
      // We're at the element that's supposed to be deleted;

      if (index == 0)
      {
        // We're supposed to remove the first element of the list.

        if (index_element->next == NULL)
        {
          // The list consists of nothing but the header element 
          // and one elemant containing data that we're supposed to delete.
          // We need to update the list pointer to point to the header el.
          (*list) = index_element->prev;
          index_element->prev->next = index_element->next;
        }
        else
        {
          // We're removing the first element of the list and need to update 
          // the list pointer.
          (*list) = index_element->next;
          index_element->next->prev = index_element->prev;
          index_element->prev->next = index_element->next;
        }
      }

      else
      {
        index_element->prev->next = index_element->next;

        if (index_element->next != NULL)
        {
          // If we're not at the last element, we need to update the previous
          // pointer of the next element
          index_element->next->prev = index_element->prev;
        }

      }

      // All preperations are made and we're ready to delete the element and
      // free it's memory.
      free(index_element);
      return;
    }


    if (index_element->next == NULL)
    {
      // If the element is the last element, but we haven't reached
      // the index of the element we want to delete yet, we just return.
      return;
    }

    index_element = index_element->next;
  }
}


int main() {
  sorted_list* l = sorted_list_create();
  
  sorted_list_add(&l, 2);
  sorted_list_add(&l, 3);
  sorted_list_add(&l, 4);
  sorted_list_add(&l, 3);
  sorted_list_add(&l, 1);
  sorted_list_remove(&l, 0);
  sorted_list_remove(&l, 1);
  sorted_list_remove(&l, 2);
  
  // expected output: 2 3
  sorted_list* iter = l;
  while(iter != NULL) {
    printf("%d ", iter->data);
    iter = iter->next;
  }
  printf("\n");
  
  sorted_list_destroy(&l);
  
  return 0;
}
