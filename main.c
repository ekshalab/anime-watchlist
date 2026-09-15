#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *title;
    int episodes_watched;
    float rating;
} Anime;

Anime *watchlist = NULL;
int count = 0;
int capacity = 0;

//grow the watchlist array when count = capacity (realloc)
//allocate space for title and copy it in safely
void add_anime(const char *title, int episodes, float rating) {
    if (count == capacity) {
        capacity = (capacity == 0) ? 4 : capacity * 2;
        watchlist = realloc(watchlist, capacity * sizeof(Anime));
    }

    watchlist[count].title = malloc(strlen(title) + 1);
    strcpy(watchlist[count].title, title);
    watchlist[count].episodes_watched = episodes;
    watchlist[count].rating = rating;
    count++;
}

//print every entry in th watchlist with index, title, episodes and ratings
void list_anime(void) {
    if (count == 0) {
        printf("Your watchlist is empty.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %d episodes - %.1f/5\n", i + 1, watchlist[i].title, watchlist[i].episodes_watched, watchlist[i].rating);
    }
}

//free the title at index, shift later entries down by one
void remove_anime(int index) {
    index = index - 1;

    if (index < 0 || index >= count) {
        printf("Invalid index.\n");
        return;
    }
    free(watchlist[index].title);
    for (int i = index; i < count - 1; i ++) {
        watchlist[i] = watchlist[i + 1];
    }
    count--;
}

//free every title string then free the array itself
void free_all(void) {
    for (int i = 0; i < count; i++) {
        free(watchlist[i].title);
    }
    free(watchlist);
    watchlist = NULL;
    count = 0;
    capacity = 0;
}

void print_menu(void) {
    printf("\n1. Add anime\n2. List anime\n3. Remove anime\n4.Exit\nChoice: ");
}

int main(void) {
    int choice;
    do {
        print_menu();
        scanf("%d", &choice);

        if (choice == 1) {
            char title[256];
            int episodes;
            float rating;
            printf("Title: ");
            scanf(" %255[^\n]", title);
            printf("Episodes watched: ");
            scanf("%d", &episodes);
            printf("Rating: ");
            scanf("%f", &rating);
            add_anime(title, episodes, rating);
        } else if (choice == 2) {
            list_anime();
        } else if (choice == 3) {
            int index;
            printf("Index to remove: ");
            scanf("%d", &index);
            remove_anime(index);
        }
    } while (choice != 4);

    free_all();
    return 0;
}