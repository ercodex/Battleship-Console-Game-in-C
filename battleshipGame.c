// Eren Çil - 152120231119

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 20 //Boyut sınırı
int COLUMN, ROW; //Eksenler
char board1[MAX_SIZE][MAX_SIZE], board2[MAX_SIZE][MAX_SIZE]; // Oyun tahtaları
char board1_s[MAX_SIZE][MAX_SIZE], board2_s[MAX_SIZE][MAX_SIZE]; // Gizli tahtalar
int record1[MAX_SIZE * MAX_SIZE][2], record2[MAX_SIZE * MAX_SIZE][2]; // Koordinatları tutan diziler
int record1_i = 0, record2_i = 0; // Kayıt dizilerinin anlık değeri
int hits1 = 0, hits2 = 0; // Oyuncuların isabetli vuruş sayıları
int turn = 1; // Oyun sırasının kimde olduğunu belirten değişken
int mov1 = 0, mov2 = 0; // Oyuncuların hamle sayılarını belirten değişken

int gameLoop() {//Oyun döngüsü
    while (1) {
        switch (turn) {
            case 1: { // Sıra oyuncu 1'de
                int shoot1_i, shoot1_j; // Atış yapılan koordinatlar
                int all_ships_destroyed1 = 0; // Döngü devamını kontrol eden flag
                
                while (!all_ships_destroyed1) {
                    printf("   ");
                    for (int coord = 0; coord < COLUMN; coord++) { // Üst koordinatları basan döngü
                        if (coord > 9) {
                            printf("\033[0;32m%d \033[0m", coord);
                        } else {
                            printf("\033[0;32m%d  \033[0m", coord);
                        }
                    }
                    printf("\n");
                    
                    for (int i = 0; i < ROW; i++) { // Yan koordinatları basan döngü
                        if (i < 10) {
                            printf("\033[0;32m%d  \033[0m", i);
                        }else{
                            printf("\033[0;32m%d \033[0m", i);
                        }

                        for (int j = 0; j < COLUMN; j++) { // İç tahtayı (noktalar) basan döngü
                            if (ROW < 10) {
                                printf("%c ", board1[i][j]);
                            } else {
                                printf("%c  ", board1[i][j]);
                            }
                        }
                        printf("\n");
                    }
                    printf("Player 1, enter coordinate to shoot: "); // Koordinatlar alınır
                    scanf("%d%d", &shoot1_j, &shoot1_i);

                    int already_shot1 = 0; // Bu koordinatın daha önce vurulup vurulmadığını kontrol eder
                    for (int k = 0; k < record1_i; k++) {
                        if (record1[k][0] == shoot1_i && record1[k][1] == shoot1_j) {
                            already_shot1 = 1;
                            break;
                        }
                    }
                    if (already_shot1) { // Kullanıcının aynı yeri vurduğuna dair uyaran koşul
                        system("cls");
                        printf("P1's total moves and hits: %d/%d\n", mov1, hits1);
                        printf("P2's total moves and hits: %d/%d\n", mov2, hits2);
                        printf("You've already shot at this coordinate.\n");
                        continue; // Yeniden koordinat iste, döngüyü devam ettir
                    }
                    record1[record1_i+1][0] = shoot1_i; // Vurulan koordinatları tutan array
                    record1[record1_i+1][1] = shoot1_j;
                    record1_i++; // İndex değerini arttır

                    if (shoot1_i >= 0 && shoot1_i < ROW && shoot1_j >= 0 && shoot1_j < COLUMN) { // Geçerli koordinat ön kontrolü
                        if (board1_s[shoot1_i][shoot1_j] == 'S') {
                            system("cls");
                            board1[shoot1_i][shoot1_j] = 'X'; // P1 Hit durumu
                            hits1++;
                            record1_i++;
                            mov1++;
                            printf("P1's total moves and hits: %d/%d\n", mov1, hits1);
                            printf("P2's total moves and hits: %d/%d\n", mov2, hits2);
                            printf("P1's last shot was a hit!\n");
                            if(hits1 == 15){
                                break;
                            }
                            turn = 1; // Sıra tekrar vuran oyuncuda
                            continue;
                        } else {
                            system("cls");
                            board1[shoot1_i][shoot1_j] = 'M'; // P1 Miss durumu
                            mov1++;
                            record1_i++;
                            printf("P1's total moves and hits: %d/%d\n", mov1, hits1);
                            printf("P2's total moves and hits: %d/%d\n", mov2, hits2);
                            turn = 2; // Oyuncu kaçırdı, sıra rakipte
                            break;
                        }
                    } else {
                        system("cls");
                        printf("P1's total moves and hits: %d/%d\n", mov1, hits1);
                        printf("P2's total moves and hits: %d/%d\n", mov2, hits2);
                        printf("Invalid coordinates. Try again.\n"); // Geçersiz koordinat girilmesi durumu
                        continue;
                    }

                    all_ships_destroyed1 = 1;
                    for (int i = 0; i < ROW; i++) {
                        for (int j = 0; j < COLUMN; j++) {
                            if (board1_s[i][j] == 'S' && board1[i][j] != 'X') {
                                all_ships_destroyed1 = 0;
                                break;
                            }
                        }
                    }
                }
                if (hits1 == 15) { // P1 tüm gemileri vurdu mu?
                    system("cls");
                    printf("All ships are destroyed, Player 1 won!\n"); // P1 kazandı
                    return 0;
                }
            }
            case 2: { // Sıra oyuncu 2'de
                int shoot2_i, shoot2_j; // Atış yapılan koordinatlar
                int all_ships_destroyed2 = 0; // Oyun sonunu kontrol eden flag

                while (!all_ships_destroyed2) {
                    printf("   ");
                    for (int coord = 0; coord < COLUMN; coord++) { // Üst koordinatları basar
                        if (coord > 9) {
                            printf("\033[0;31m%d \033[0m", coord);
                        } else {
                            printf("\033[0;31m%d  \033[0m", coord);
                        }
                    }
                    printf("\n");
                    
                    for (int i = 0; i < ROW; i++) { // Yan koordinatları basar
                        if (i < 10) {
                            printf("\033[0;31m%d  \033[0m", i);
                        }else{
                            printf("\033[0;31m%d \033[0m", i);
                        }

                        for (int j = 0; j < COLUMN; j++) { // İç tahtayı basar
                            if (ROW < 10) {
                                printf("%c ", board2[i][j]);
                            } else {
                                printf("%c  ", board2[i][j]);
                            }
                        }
                        printf("\n");
                    }
                    printf("Player 2, enter coordinate to shoot: "); // Koordinatlar alınır
                    scanf("%d%d", &shoot2_j, &shoot2_i);

                    int already_shot2 = 0; // Bu koordinatın daha önce vurulup vurulmadığını kontrol eder
                    for (int k = 0; k < record2_i; k++) {
                        if (record2[k][0] == shoot2_i && record2[k][1] == shoot2_j) {
                            already_shot2 = 1;
                            break;
                        }
                    }

                    if (already_shot2) { // Önceden vurulan noktayı kontrol et
                        system("cls");
                        printf("P1's total moves and hits: %d/%d\n", mov1, hits1);
                        printf("P2's total moves and hits: %d/%d\n", mov2, hits2);
                        printf("P2, you've already shot at this coordinate.\n");
                        continue; // Yeniden koordinat iste, döngüyü devam ettir
                    }

                    // Kayıt tutan array?
                    record2[record2_i+1][0] = shoot2_i;
                    record2[record2_i+1][1] = shoot2_j;
                    record2_i++; // İndex değerini arttır

                    if (shoot2_i >= 0 && shoot2_i < ROW && shoot2_j >= 0 && shoot2_j < COLUMN) {
                        if (board2_s[shoot2_i][shoot2_j] == 'S') {
                            system("cls");
                            board2[shoot2_i][shoot2_j] = 'X'; // P2 Hit mesajı
                            hits2++;
                            record2_i++;
                            mov2++;
                            printf("P1's total moves and hits: %d/%d\n", mov1, hits1);
                            printf("P2's total moves and hits: %d/%d\n", mov2, hits2);
                            printf("P2's last shot was a hit!\n");
                            if (hits2 == 15){
                                break;
                            }
                            turn = 2; // Sıra tekrar vuran oyuncuda
                            continue;
                        } else {
                            system("cls");
                            board2[shoot2_i][shoot2_j] = 'M'; // P2 Miss mesajı
                            mov2++;
                            record2_i++;
                            printf("P1's total moves and hits: %d/%d\n", mov1, hits1);
                            printf("P2's total moves and hits: %d/%d\n", mov2, hits2);
                            turn = 1; // Oyuncu kaçırdı, sıra rakipte
                            break;
                        }
                    } else {
                        system("cls");
                        printf("P1's total moves and hits: %d/%d\n", mov1, hits1);
                        printf("P2's total moves and hits: %d/%d\n", mov2, hits2);
                        printf("Invalid coordinates. Try again.\n"); // Geçersiz koordinat girilmesi durumu
                        continue;
                    }

                    all_ships_destroyed2 = 1;
                    for (int i = 0; i < ROW; i++) {
                        for (int j = 0; j < COLUMN; j++) {
                            if (board2_s[i][j] == 'S' && board2[i][j] != 'X') {
                                all_ships_destroyed2 = 0;
                                break;
                            }
                        }
                    }
                }
                if (hits2 == 15) { // P2 tüm gemileri vurdu mu?
                    system("cls");
                    printf("All ships are destroyed, Player 2 won!\n"); // P2 kazandı
                    return 0;
                }
            }
        }
    }
}
void getBoardSize(){ // Tahta boyutu alan fonksiyon
    printf("Enter board size (ROW COLUMN): ");
    scanf("%d%d", &ROW, &COLUMN);
}
void placeShipForPlayer(char board[][MAX_SIZE], int player) {
    srand((unsigned int)(time(NULL) + player)); // Bilgisayar zamanını kullanarak rastgelelik

    for (int shipMaxL = 1; shipMaxL < 6; shipMaxL++) { // Genel gemi yerleştirme döngüsü
        int ship_i, ship_j, direction, b;

        do {
            ship_i = rand() % ROW; // Rastgele bir koordinat seç
            ship_j = rand() % COLUMN; // Rastgele bir koordinat seç
            direction = rand() % 2; // Dikey/Yatay rastgele seç
            b = 0;

            int validPlacement = 1;

            if (direction == 0) { // Yatay yerleştirme kontrolü
                for (int k = 0; k < shipMaxL; k++) {
                    if (ship_j + k >= COLUMN || board[ship_i][ship_j + k] == 'S' || 
                                (ship_i - 1 >= 0 && board[ship_i - 1][ship_j + k] == 'S') ||
                                (ship_i + 1 < ROW && board[ship_i + 1][ship_j + k] == 'S') ||
                                (ship_j + k - 1 >= 0 && board[ship_i][ship_j + k - 1] == 'S') ||
                                (ship_j + k + 1 < COLUMN && board[ship_i][ship_j + k + 1] == 'S') ||
                                (ship_i - 1 >= 0 && ship_j + k - 1 >= 0 && board[ship_i - 1][ship_j + k - 1] == 'S') ||
                                (ship_i - 1 >= 0 && ship_j + k + 1 < COLUMN && board[ship_i - 1][ship_j + k + 1] == 'S') ||
                                (ship_i + 1 < ROW && ship_j + k - 1 >= 0 && board[ship_i + 1][ship_j + k - 1] == 'S') ||
                                (ship_i + 1 < ROW && ship_j + k + 1 < COLUMN && board[ship_i + 1][ship_j + k + 1] == 'S')) {
                        validPlacement = 0;
                        break;
                    }
                }

                if (validPlacement) { // Koordinat onay alırsa gemi parçasını yerleştir
                    for (int k = 0; k < shipMaxL; k++) {
                        board[ship_i][ship_j + k] = 'S';
                        b++;
                    }
                }
            } else { // Dik yerleştirme kontrolü
                for (int k = 0; k < shipMaxL; k++) {
                    if (ship_i + k >= ROW || board[ship_i + k][ship_j] == 'S' || 
                                (ship_j - 1 >= 0 && board[ship_i + k][ship_j - 1] == 'S') ||
                                (ship_j + 1 < COLUMN && board[ship_i + k][ship_j + 1] == 'S') ||
                                (ship_i + k - 1 >= 0 && board[ship_i + k - 1][ship_j] == 'S') ||
                                (ship_i + k + 1 < ROW && board[ship_i + k + 1][ship_j] == 'S') ||
                                (ship_i - 1 >= 0 && ship_j - 1 >= 0 && board[ship_i - 1][ship_j - 1] == 'S') ||
                                (ship_i - 1 >= 0 && ship_j + 1 < COLUMN && board[ship_i - 1][ship_j + 1] == 'S') ||
                                (ship_i + k + 1 < ROW && ship_j - 1 >= 0 && board[ship_i + k + 1][ship_j - 1] == 'S') ||
                                (ship_i + k + 1 < ROW && ship_j + 1 < COLUMN && board[ship_i + k + 1][ship_j + 1] == 'S')) {
                        validPlacement = 0;
                        break;
                    }
                }

                if (validPlacement) { // Koordinat onay alırsa gemi parçasını yerleştir
                    for (int k = 0; k < shipMaxL; k++) {
                        board[ship_i + k][ship_j] = 'S';
                        b++;
                    }
                }
            }
        } while (b < shipMaxL);
    }
}
void fillBoard(){ // Oyuncuların gördükleri tahtaları noktalarla dolduran fonksiyon
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            board1[i][j] = '.';
            board2[i][j] = '.';
        }
    }
}
int checkSize(){ // Boyut kontrolü yapan fonksiyon
    if (ROW < 1 || ROW > MAX_SIZE || COLUMN < 1 || COLUMN > MAX_SIZE) {
        printf("Invalid board size. Please enter values between 1 and %d.\n", MAX_SIZE);
        return 1; // Hata kodu ile programı sonlandır
    }
}
int main() { // Ana fonksiyon
    int is_size_true = 0;
    while (is_size_true == 0) { // Oyun başlangıcı, tahta boyutu geçerliyse çalışır
        if (ROW <10 || COLUMN <10) {
            system("cls");
            printf("->Welcome to the Battleship game!\n");
            printf("->Made by Eren Cil, have fun!\n\n");
            printf("P1 is color Red, shoots Green.\n");
            printf("P2 is color Green, shoots Red.\n");
            printf("Minimum 10 is allowed for Rows and Columns both.\n\n");
            getBoardSize();
            is_size_true = 0;
        } else {
            system("cls");
            printf("Board size accepted!\n");
            is_size_true = 1;
        }
    }
    checkSize();
    if (is_size_true == 1) { // Boyut kabul edildiyse devam
        fillBoard();
        placeShipForPlayer(board1_s, 1);
        placeShipForPlayer(board2_s, 2);
        gameLoop();
    }
    return 0;
}