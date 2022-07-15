#include <iostream>
#include <cassert>
#define RUN_TESTS 1

using namespace std;

bool f_word_has_ch (const char* word, int size, char letter) {
    /* Check if the letter is contained in the word */
    for (int i = 0; i < size; ++i)
        if (word[i] == letter)
            return true;
    return false;
}

bool test_word_has_ch() {
    /* Tests for the function f_in_word */
    assert (f_word_has_ch("ciao", 5, 'c') == true);
    assert (f_word_has_ch("eheh", 5, 't') == false);
    assert (f_word_has_ch("123", 4, '2')  == true);
    cout << "test f_word_has_ch: SUCCESS" << endl;
}


bool f_str_in_str(const char* w1, int s1, const char* w2, int s2) {
    /* Check if every letter of w1 is contained in w2 */
    for (int i = 0; i < s1 - 1; ++i)
        if (!f_word_has_ch(w2, s2, w1[i]))
            return false;
    return true;
}

void test_str_in_str() {
    assert (f_str_in_str("ciao", 5, "abcdejacoi", 11) == true);
    assert (f_str_in_str("eh", 3, "fg", 3) == false);
    assert (f_str_in_str("prova", 6, "prov", 5) == false);
    cout << "TEST: str_in_str: OK" << endl;
}

void f_display (const char* w1, int s1, const char* mask, int s2){
    /* Display the letters in w1 only when contained into mask */
    for (int i = 0; i < s1; ++i)
        if (f_word_has_ch(mask, s2, w1[i]))
            cout << " " << w1[i] << " ";
        else 
            cout << " - ";
    cout << endl;
}

void test_display() {
    cout << "Expected: c - a - : " << endl;
    f_display("ciao", 5, "abc", 4);
    cout << "Expected: c o m p l e t e " << endl;
    f_display("complete", 9, "completq", 9);
    cout << "Expected: - - l l " << endl;
    f_display("roll", 5, "l", 2);
    cout << "Expected: - - - -" << endl;
    f_display("cute", 5, "abd", 4);
    cout << "Expected: - - - - - " << endl;
    f_display("prova", 5, "", 1);
}

void f_extend (char* &str, int* size, char newchar) {
    /* Extend the string str by adding a new character at the end */
    /* it assumed to work with strings, so size at least 1 for '\0' */
    assert (*size >= 1);
    char* ptrNewstr = new char[*size + 1];
    int i = 0;
    for (i = 0; i < *size - 1; ++i) {
        ptrNewstr[i] = str[i];
    }
    ptrNewstr[i] = newchar;
    ptrNewstr[i + 1] = '\0';
    delete [] str;
    str = ptrNewstr;
    *size+=1;
}

void test_extend() {
    /* Run various examples */
    int size1 = 5;
    char* test1 = new char[5];
    test1[0] = 'c';
    test1[1] = 'i';
    test1[2] = 'a';
    test1[3] = 'o';
    test1[4] = '\0';
    cout << test1 << endl;
    f_extend(test1, &size1, 'S');
    cout << test1 << endl;
    assert (size1 == 6);
    delete [] test1;


    int size2 = 1;
    char* test2 = new char[1];
    test2[0] = '\0';
    f_extend(test2, &size2, 'C');
    cout << test2 << endl;
    assert (size2 == 2);
    assert (test2[0] == 'C' && test2[1] == '\0');
    delete [] test2;

    int size3 = 2;
    char* test3 = new char[size3];
    test3[0] = 'B';
    test3[1] = '\0';
    f_extend(test3, &size3, 'D');
    cout << test3 << endl;
    assert (size3 == 3);
    assert (test3[0] == 'B' && test3[1] == 'D' && test3[2] == '\0');
    delete [] test3;
}


void printstr (const char* str, int sz) {
    for (int i = 0; i < sz; ++i)
        cout << str[i];
}

int main() {

#if RUN_TESTS
    test_word_has_ch();
    test_display();
    test_extend();
    test_str_in_str();
#else

    const char* secret = "ciao";
    int sz_secret = 5;
    int lifes = sz_secret + 5;
    char* guessed = new char[1];
    guessed[0] = '\0';
    int sz_guessed = 1;

    /* The game continues until lifes == 0, or each letter is guessed. */
    for (char userch = '0';;){
        /* Check if the conditions are met: if yes break */
        if (f_str_in_str(secret, sz_secret, guessed, sz_guessed)){
            lifes += 1;
            break;
        }
        if (lifes <= 0)
            break;
        /* Print the word */
        f_display (secret, sz_secret, guessed, sz_guessed);
        cout << "Remaining attempts: " << lifes << endl;

        /* If in game, ask for user input: a single letter */
        cout << "Insert your letter: " << endl;
        cin >> userch;

        /* Extend the guessed by adding such a letter, decrease one life */
        f_extend (guessed, &sz_guessed, userch);
        lifes -= 1;
        cout << "Inserted letters :";
        printstr(guessed, sz_guessed);
        cout << endl;
    }

    /* Out of the game loop */
    if (lifes == 0) {
        cout << "GAME OVER" << endl;
    } else {
        cout << "YOU WIN" << endl;
    }

    delete [] guessed;
#endif
    return 0;
}
