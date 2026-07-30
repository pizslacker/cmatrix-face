#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// --- ASCII ART PLACEHOLDER ---
// You will replace this with the ASCII version of your photo.
#define FACE_WIDTH 104
#define FACE_HEIGHT 52
const char *face_ascii[FACE_HEIGHT] = {
"KKKKKKKKKKKKKK0000000000OOOOOkddoc::ccc:;,.....  ..   .... ..,,'..',;;;;;,;:;,,'';;;:ccccccloxxxxxkkkkkx",
"KKKKKKKKKKKKKKKKK00000OOOOkxxdl:::cc;;,........        ......'''.',,,,,,,;;,........,::;;;cclddddxkkkkkk",
"KKKKKKKKKKKKKKKKKK00000OOxdxo:;,,,:c;.........             .....''....',,'..       .....',::clooddxkkkkx",
"KKKKKKKKKKKKKKKKKK0000Okxoloc;,'',coc,...    .        ......   .......''....       ....';:::::clodxkkxdd",
"KKKKKKKKKKKKKKKKKK000OOxdl:;'....'','....             .,;,..    ...',,,,'''''....    ..,;;,,,,;cloxkkxdo",
"XXXKKKKKKKKKKKKKKKK0000Oxoc;.............         .....'...   ..',;::;;;,,',,'....   .........':lodkkxxo",
"XKKKKKKXKKKKKKKKKKK0000Okdl:'.....''''...        .',,''''..  ..';:;:::;;,,,'''..            ..':lodkkkxd",
"KKKKKKKKKKKKKKKKK0OOOOOkkxdc;'''',,,'.......   ...''...',,,'.....'...............            .':lldO0Okx",
"KKKKKKKKKKKKKKKKOkdodxxddoolc:;;:cc:,'....   ..........,:::;;,,,,,,'...    .......           .,clooxkOkk",
"KKKKKKKKKKKKK00Oxolloddddlc::ccloool:,'....  ..''.    .,:clccccc::::;,'............          .:loddxkkOk",
"XXXKKKKKKKKKK0Okdllodxkkxl:;;;:cllcclccc:,... ..'.....',:clllllllcccc:;;,,'''.......        .,lddddxkOOO",
"XXXKKKKKKKKKKK0kdooddxxdlc::;::::cccoooddl;....,;'....';:cloooolllcccc::::;;;,'........    ..cdxxddxkOOO",
"XXXXXXXKKKKKKK0kddoollccc:;;;;;,,:::::::::'.....;'...';clllooooollcccccccc:::;;;;:::;;,'....,lxxkkkkkOOO",
"XXXXXXXKKXXKKK0xlcc:;;;;,'......',,',''''...   ....',;cooddddddddollc:ccllccc:::cclllllc,...;lodxxkkOOO0",
"XXXXXXXXXXXXKK0Odc:,'''.........''.........    ..',;:clodxxxddddddolllllllccccccllloooooc,.':l::codxkO0K",
"XXXXKXXXXXXKKK00Okxdl:,'................      ..,;:cccldxkkkxxxxxddooooollllllllllooddddoc,,::;:clloxOKX",
"XXXXKXXXXXXKKK0Oxdoddl;'..............      ..';:cllllodxkOOOkxxxxxxddddddooolllooooddxxxo:,,;clloooxO0X",
"XXXXXXXXXXXXXK0Oxdddo:'.... ..   ....    ..,;;:clloooodxkOO0Okxxxdddddddddddooooddddxxkkkxl::lodoooodk0K",
"XXXXXXXXXXXXXK0kolcc;,.......          ..;:ccclloooooddxk00OOkxxdddddddddddddddddddxxkkkkkdllodxdolldkO0",
"XXXXXXXXXXXXXXK0xollc;,....           ..;cllllllooodddddxkkxxddooooooooooooooooddddxxkkkkkxocloooooodkO0",
"XXXXXKXXXXXXXXK0kdddo:,...            .;cllllllooolcc:;;::::::;;;:::cclllllllccloooddxxxxkxolodxxxxxkkO0",
"XXXXXXXXXXXXXKK00OOkdc,...           .,cloooooollc:;;,,,,''''.........';:::ccccllllooodddxxoodkkOOOkkOO0",
"KKKKKKKKKKKKKKKK000Od:,.....        .,cooddooolcc:::::;;;;,,,,'.....  ..''',:::ccccllloooddooxOOOOOOkkO0",
"KKKKKKKKKKKKKKKK00Oxoc:,.......    .,:lodddoolc::;;,,''....................';::::::;;;;;;::cokOOOOOOkkOO",
"XXXXXXXXXXXXXXXXKK0kdl:'...',,.  .';:clodddoolc::;,'''......''.    ..'','',;;:::;,'.......';ok00OOOkkkkO",
"XXXXXXXXXXXXXXXXXK0kdl,.........';:clooodddddoollllcc::;;,''''... ...',,;;:cclc:;'.......';cdk00OOkkkkkO",
"XXXXXXXXXXXXXXXXXK0Oxl:;,...',;;:cclooodddxddddddooollc::;;;;,,'''''',,;:ccllooc,'''.   .,oxkO00OkkkkkkO",
"XXXXXXXXXXXXXXXXXKK0xoool:,;clllcclloooddddddddddddddolcc:;;,,,,,,;;;;:cloodddxo;'',,...:dkOOO00Okxxxxkk",
"XXXXXXXXXXXXXXKK00Okdoooolc:clolccllooodoooodddddddddddddolc:::::::cccloddxxxxkxl;,,;:cokO00OOOOOkkkxkkk",
"XXXXXXXXXXXXXXKK0Okdc:looollllllllloooooooodddddxxxxxxxxxxddollcc::ccloodxxkkkkkxl:;;:lxO000OOOOOkkkkxxk",
"XXXXXXXXXXXXXXXKK0ko,.':lolllloollloooddoodddddxxxxxxxxxxddddolc:;;;:lloddxkkkOOOxollloxOKK0OOOOOkxxxxxx",
"XXXXXXXXXXXXXXXK0Odc'  .':cccloooooooddddoodddddddddddddddooolc:,,:looooddxxkkkOOkxdddxxO000Okxdxxxxxxxx",
"XXXXXXXXXXXXXXXXKOo:,.  ..;:clllooooddddoooooooooooooooollllc:;,';loddddoddddxxxkkxdodxkkOOOOkkddxxxxxxx",
"XXXXKKKKK00OOkdlc:,.    .';cllllllooodoooooooooolllllllccc::;;;,,;cllllcccccclllooollodxk000OkkOOkxxddxx",
"OOkkxxdddoooll:'.  .    .,:clllllllooooooolllllllllcccc::;;;;;:::;,,,,'''',;;:::ccccclodxkO0OkkkOkxxxddx",
":::cccclllllll:,.      .,::lllllccllloooollllllllcc:;;;;;;;;;::cc:,''''''',;;::::;;;:cooooxOOkxkOkxxxddd",
";;;;;:clllllc:,..      .,:cllllccccllllllllcclllc:;;;;;;;;;;;:cccc:;;,,,,,;;:ccc:;,;:oxxddkOOkxkOOkxxddd",
";;;,',;:cccc:;..        ,clllllccc:cccllllllcccc:::;;;,...',;:cllllc:::::;;:cllc:,,;lxOxooxOOxdxOOkxxddd",
":;;;,..';;:::;.         'clllllcc:::cccclllcccc::::;;,,''..'',,;;:::::::cccllol:;;coxkOOxdxOOkddkOkxxddd",
":;;;;'....,;:;.         'clllllcc::;:ccccccccc:::::;;;;;;;:;;;;;,,''''',,;;:ccc:clxOOOO0OOOOOxddxOkxxxdd",
",,,,,,'.. .',,.         'cllllcccc:;;;::::ccc:::::::;:::::::ccccccc:;;;;::clllcldkO00OO00000Okdodkkxxxxd",
".....',''......         ,cllllcccc::;;;;::::::::::::::::ccccllc::::::::::clloodkOO0000O000000kdlokkxxxxd",
"......',,'.....         ,cllllccc:::;;,,;;;:::::::::::::::clllcc:;;,''',;clllcloooooddxkOO000Oxllxkkxxxx",
"''....',,''....         'cllllccc::::;;,,,'',;;:::::::;;;:ccllc:::,'...';cllc,'.....'',;;:d000xlcdkkxxxd",
"......''''......        .:lllccc:::;;;;;;,'...',,;;;;;,,;:ccllcccc:,,,,:clol::::;,,'......:k00kl:okkxxxx",
".....',;;,......         ,ccccc::::;;;;;;;,'......'',,;:ccllllllllcc::clloo:'';:::;,'.....;k00Oo:lxkxxxx",
".....';::;;,'...         .;:cc:::;;;;;;,;,,,,'..  ....,;:::ccclllcccccclool,...',,;;''...'lk00Od:cxkxxdd",
".....'',,;,,''..          .;::::;;;;;;;;;,,,,,,'.. ....',,,,;:::ccc:::cclc;....''',;'.  .;ok000x::dxxxxk",
"........',,,,'..           .,;;;;;;;;;;,,,;;;;;;,,'.........'',,;;,,;;;;,..  ...'''','..';;:cokx:,okO000",
"........'''.....            .',,,,,,,,,,,,,,;;;;;;;;;,''..   ...........        ....,c:..,;,,,:l;'ck0000",
".... ...'..        .;.       ..',,,,,,,,,,,,,,,;;;::::ldxo:'',,.                   ..:do;';;;,,,,,:dkkkO",
"..........         ,l:.       ...''',,,,''''',,,;::;,:oxkkxlcodc.                   .'oko,,;::;,,,;:llod"
};

// State machine for the face fade effect
typedef enum {
    STATE_WAITING,
    STATE_FADING_IN,
    STATE_HOLDING,
    STATE_FADING_OUT
} FaceState;

int main() {
    // 1. Initialize ncurses
    initscr();
    start_color();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);
    srand(time(NULL));

    // Define color pairs for the Matrix and the Face
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // Normal Matrix green
    init_pair(2, COLOR_WHITE, COLOR_BLACK); // Bright Matrix heads / Brightest face
    init_pair(3, COLOR_CYAN, COLOR_BLACK);  // Intermediate fade color

    int width = COLS;
    int height = LINES;

    // Array to track the Y position of the "head" of the matrix rain for each column
    int drops[width];
    for (int i = 0; i < width; i++) {
        drops[i] = rand() % height;
    }

    // Face state tracking
    FaceState face_state = STATE_WAITING;
    int face_timer = 0;
    int fade_level = 0; // 0 = invisible, 1 = dim green, 2 = bold green, 3 = white

    while (1) {
        // Check for exit
        int ch = getch();
        if (ch == 'q' || ch == 'Q') {
            break;
        }

        // Handle terminal resize gracefully
        if (COLS != width || LINES != height) {
            width = COLS;
            height = LINES;
            for (int i = 0; i < width; i++) {
                drops[i] = rand() % height;
            }
        }

        // --- DRAW MATRIX RAIN ---
        // Dim the screen slightly by randomly overwriting characters with spaces
        for (int i = 0; i < width * height / 40; i++) {
            mvaddch(rand() % height, rand() % width, ' ');
        }

        // Draw the falling drops
        for (int i = 0; i < width; i++) {
            // Randomly print a character at the current drop head
            char c = 33 + (rand() % 94); 
            
            // Draw head (white)
            attron(COLOR_PAIR(2) | A_BOLD);
            mvaddch(drops[i], i, c);
            attroff(COLOR_PAIR(2) | A_BOLD);

            // Draw tail (green) just above the head
            if (drops[i] > 0) {
                char tail_c = 33 + (rand() % 94);
                attron(COLOR_PAIR(1));
                mvaddch(drops[i] - 1, i, tail_c);
                attroff(COLOR_PAIR(1));
            }

            // Move drop down
            drops[i]++;
            
            // Reset drop to top randomly when it hits the bottom
            if (drops[i] >= height && (rand() % 10) > 7) {
                drops[i] = 0;
            }
        }

        // --- HANDLE FACE FADE LOGIC ---
        face_timer++;

        switch (face_state) {
            case STATE_WAITING:
                if (face_timer > 300) { // Wait ~15 seconds (depends on usleep)
                    face_state = STATE_FADING_IN;
                    face_timer = 0;
                    fade_level = 0;
                }
                break;
            case STATE_FADING_IN:
                if (face_timer % 10 == 0) fade_level++;
                if (fade_level >= 3) {
                    face_state = STATE_HOLDING;
                    face_timer = 0;
                }
                break;
            case STATE_HOLDING:
                if (face_timer > 100) { // Hold for ~5 seconds
                    face_state = STATE_FADING_OUT;
                    face_timer = 0;
                }
                break;
            case STATE_FADING_OUT:
                if (face_timer % 10 == 0) fade_level--;
                if (fade_level <= 0) {
                    face_state = STATE_WAITING;
                    face_timer = 0;
                }
                break;
        }

        // --- DRAW THE FACE ---
        if (face_state != STATE_WAITING && fade_level > 0) {
            int start_x = (width - FACE_WIDTH) / 2;
            int start_y = (height - FACE_HEIGHT) / 2;

            // Determine color based on fade level
            int attr = COLOR_PAIR(1);
            if (fade_level == 2) attr = COLOR_PAIR(1) | A_BOLD;
            if (fade_level >= 3) attr = COLOR_PAIR(2) | A_BOLD;

            attron(attr);
            for (int y = 0; y < FACE_HEIGHT; y++) {
                for (int x = 0; x < FACE_WIDTH; x++) {
                    if (face_ascii[y][x] != ' ') {
                        // Only draw non-space characters to let the matrix show through
                        mvaddch(start_y + y, start_x + x, face_ascii[y][x]);
                    }
                }
            }
            attroff(attr);
        }

        refresh();
        usleep(50000); // 50 milliseconds delay (~20 frames per second)
    }

    // Clean up ncurses on exit
    endwin();
    return 0;
}
