#include "Tree.h"
#include <iostream>
#include <fstream>
bool is_correct(string a) {
    int count_right=1, count_left=0;
    if (a[0]!='(') return false;
    for (int i=1;i<a.length();i++) {
        if (a[i]=='(') {
            count_right++;
        }
        else if (a[i]==')') {
            count_left++;
        }
        else if (isdigit(a[i])|| a[i]==' '){}
        else return false;
    }
    return count_right==count_left;
}
int main() {
    ifstream myfile("../input.txt");
    string a;
    if (myfile.is_open()) {
        getline(myfile, a);
    }
    if (is_correct(a)) {
        Red_Black b;//КЧ дерево
        Tree c;//Обычное бмнорное
        Array d;
        b.make_Tree(a);
        c.make_Tree(a);
        c.direct_traverse(&d,c.get_root());
        cout<<"Binary tree:"<<endl;
        cout<<"Direct traverse: ";
        for (int i=0;i<d.get_length();i++) {
            cout<<d[i]<<' ';
        }
        cout<<endl;
        cout<<"Red Black Tree:"<<endl;

        d = b.width_traverse();
        cout<<"Width traverse: ";
        for (int i=0;i<d.get_length();i++) {
            cout<<d[i]<<' ';
        }
        cout<<endl;
        d = b.direct_traverse();
        cout<<"Direct traverse: ";
        for (int i=0;i<d.get_length();i++) {
            cout<<d[i]<<' ';
        }
        cout<<endl;
        d = b.centered_traverse();
        cout<<"Centered traverse: ";
        for (int i=0;i<d.get_length();i++) {
            cout<<d[i]<<' ';
        }
        cout<<endl;
        d = b.reverse_traverse();
        cout<<"Reverse traverse: ";
        for (int i=0;i<d.get_length();i++) {
            cout<<d[i]<<' ';
        }
        cout<<endl;

    }
    else cout<<"Incorrect input";
    return 0;
}