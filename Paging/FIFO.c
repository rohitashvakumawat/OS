#include <stdio.h>
#include <stdbool.h>

struct PageTable {
    int frame_no;
    bool valid;
};

bool isPagePresent(struct PageTable PT[], int page, int n) {
    return PT[page].valid;
}

void updatePageTable(struct PageTable PT[], int page, int fr_no, bool status) {
    PT[page].valid = status;
    PT[page].frame_no = fr_no;
}

void printFrameContents(int frame[], int no_of_frames) {
    for (int i = 0; i < no_of_frames; i++)
        printf("%d\t", frame[i]);
    printf("\tM\n");
}

void printFrameContentsH(int frame[], int no_of_frames) {
    for (int i = 0; i < no_of_frames; i++)
        printf("%d\t", frame[i]);
    printf("\tH\n");
}

int main() {
    printf("Enter the no. of pages: ");
    int n;
    scanf("%d", &n);

    int reference_string[n];

    printf("Enter the reference string (different page numbers): ");
    for (int i = 0; i < n; i++)
        scanf("%d", &reference_string[i]);

    printf("Enter the no. of frames you want to give to the process: ");
    int no_of_frames;
    scanf("%d", &no_of_frames);

    int frame[no_of_frames];
    for (int i = 0; i < no_of_frames; i++)
        frame[i] = -1;

    struct PageTable PT[50];
    for (int i = 0; i < 50; i++) {
        PT[i].frame_no = -1;
        PT[i].valid = false;
    }

    printf("\n  The Contents inside the Frame array at different times:  \n\n");
    for (int i = 0; i < no_of_frames; i++) {
        printf("F%d\t", i);
    }
    printf("Hit(H) or Miss(M)\n");

    int page_fault = 0, page_hits = 0, current = 0;
    bool flag = false;

    for (int i = 0; i < n; i++) {
        if (!isPagePresent(PT, reference_string[i], n)) {
            page_fault++;

            if (!flag && current < no_of_frames) {
                frame[current] = reference_string[i];
                printFrameContents(frame, no_of_frames);
                updatePageTable(PT, reference_string[i], current, true);
                current++;
                if (current == no_of_frames) {
                    current = 0;
                    flag = true;
                }
            } else {
                updatePageTable(PT, frame[current], -1, false);
                frame[current] = reference_string[i];
                printFrameContents(frame, no_of_frames);
                updatePageTable(PT, reference_string[i], current, true);
                current = (current + 1) % no_of_frames;
            }
        } else {
            printFrameContentsH(frame, no_of_frames);
            page_hits++;
        }
    }

    printf("\nTotal No. of Page Faults = %d\n", page_fault);
    printf("Total No. of Page Hits = %d\n", page_hits);
    printf("\nPage Fault ratio = %.2f\n", (float)page_fault / n);
    printf("Page Hit Ratio = %.2f\n", (float)page_hits / n);

    return 0;
}