#include <iostream>
#include <cassert>

#define RUN_TESTS 1

using namespace std;


bool f_in_word (const char* word, int size, char letter) {
    /* Check if the letter is contained in the word */
    for (int i = 0; i < size; ++i)
        if (word[i] == letter)
            return true;
    return false;
}


bool test_in_word () {
    /* Tests for the function f_in_word */
    assert (f_in_word("ciao", 5, 'c') == true);
    assert (f_in_word("eheh", 5, 't') == false);
    assert (f_in_word("123", 4, '2')  == true);
    cout << "test f_in_word: SUCCESS" << endl;
}


void f_display (const char* w1, int s1, const char* mask, int s2){
    /* Display the letters in w1 only when contained into mask */
    for (int i = 0; i < s1; ++i)
        if (f_in_word(mask, s2, w1[i]))
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


void f_extend (char* &str, int size, char newchar) {
    /* Extend the string str by adding a new character at the end */
    char* ptrNewstr = new char[size + 1];
    int i = 0;
    for (i = 0; i < size - 1; ++i) {
        ptrNewstr[i] = str[i];
    }
    ptrNewstr[i] = newchar;
    ptrNewstr[i + 1] = '\0';
    delete [] str;
    str = ptrNewstr;
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
    f_extend(test1, 5, 'S');
    cout << test1 << endl;
    delete [] test1;
}

int main() {

#if RUN_TESTS
    test_in_word();
    test_display();
    test_extend();

#endif

    return 0;
}
