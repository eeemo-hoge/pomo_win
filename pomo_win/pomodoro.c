#include<stdio.h>
#include<time.h>

// Function to clear input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    int minutes;
    printf("Enter the number of minutes for the Pomodoro timer: ");
    scanf("%d", &minutes);
    
    int break_minutes;
    printf("Enter the number of minutes you want to break for: ");
    scanf("%d", &break_minutes);
    
    int sessions;
    printf("How many sessions do you want (in number of sessions)? ");
    scanf("%d", &sessions);
    
    int long_break_minutes;
    printf("How many minutes do you want to take a long break for? ");
    scanf("%d", &long_break_minutes);
    
    clear_input_buffer(); // Clear input buffer after scanf
    
    int long_break_counter = 0;

    for(int session = 1; session <= sessions; session++) {
        printf("\n=== Session %d/%d ===\n", session, sessions);
        printf("Pomodoro timer started for %d minutes.\n", minutes);
        
        // Convert minutes to seconds
        int seconds = minutes * 60;
        
        // Start the timer for THIS session
        time_t start_time = time(NULL);
        
        // Work timer
        while (1) {
            // Calculate elapsed time
            time_t current_time = time(NULL);
            double elapsed_seconds = difftime(current_time, start_time);
            int progress = (int)((elapsed_seconds / seconds) * 100);
            
            if (progress > 100) progress = 100;
            
            printf("\rWork Time - [");
            for(int j = 0; j < progress; j++) {
                printf("#");
            }
            for(int j = progress; j < 100; j++) {
                printf(" ");
            }
            printf("] %d%%", progress);
            fflush(stdout);

            if (elapsed_seconds >= seconds) {
                printf("\nSession %d/%d - Timer has finished!\n", session, sessions);
                printf("\a"); // Beep sound
                printf("Time's up! Take a break.\n");
                break;
            }
        }
    
        // Decide break type
        long_break_counter++;
        int is_long_break = (long_break_counter == 4); // Long break every 4 sessions
        
        int current_break_minutes = is_long_break ? long_break_minutes : break_minutes;
        int break_seconds = current_break_minutes * 60;
        
        if (is_long_break) {
            printf("\n=== Long Break Time! ===\n");
            long_break_counter = 0; // Reset counter
        } else {
            printf("\n=== Break Time ===\n");
        }
        
        printf("Break duration: %d minutes\n", current_break_minutes);
        
        time_t break_start = time(NULL);
        
        while (1) {
            time_t break_current = time(NULL);
            double break_elapsed = difftime(break_current, break_start);
            int break_progress = (int)((break_elapsed / break_seconds) * 100);
            
            if (break_progress > 100) break_progress = 100;
            
            printf("\r%s - [", is_long_break ? "Long Break" : "Break Time");
            for(int j = 0; j < break_progress; j++) {
                printf("#");
            }
            for(int j = break_progress; j < 100; j++) {
                printf(" ");
            }
            printf("] %d%%", break_progress);
            fflush(stdout);
            
            if (break_elapsed >= break_seconds) {
                printf("\n%s finished!\n", is_long_break ? "Long break" : "Break");
                printf("\a"); // Beep sound
                
                break;
            }
        }
    }
    
    printf("\n\n=== All sessions completed! Great work! ===\n");
    
    return 0;
}
