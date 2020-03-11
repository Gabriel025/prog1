int main(int argc, char **argv)
{
    //egész                                              int a;
    //egészre mutató mutató                              int *pa;
    //egész referenciája                                 int &ra = a; //(csak C++)
    //egészek tömbje                                     int arr[N]; //ha N nem konstans, akkor VLA-t kapunk (C99)
    //egészek tömbjének referenciája (nem az első elemé) int (&rarr)[N] = arr;
    //egészre mutató mutatók tömbje                      int *parr[N];
    //egészre mutató mutatót visszaadó függvény          int *func()[N];
    //egészre mutató mutatót visszaadó
    //    függvényre mutató mutató                        int *(*funcp)()[N] = func;
    //egészet visszaadó és két egészet kapó függvényre   
    //    mutató mutatót visszaadó, egészet kapó függvény int (*func2(int))(int, int);
    //függvénymutató egy egészet visszaadó és két
    //    egészet kapó függvényre mutató mutatót
    //    visszaadó, egészet kapó függvényre              int (*(*func2p)(int))(int, int);

    int a; //a egy egész

    int *b = &a; //b egy egészre mutató mutató ami a-ra mutat

    int &r = a; //r egy (lvalue) referencia a-ra

    int c[5]; //c egy öt egészből álló tömb

    int (&tr)[5] = c; //tr egy referencia c-re 

    int *d[5]; //d egészre mutató mutatók 5 elemű tömbje

    int *h(); //h egy egészre mutató mutatót visszaadó függvény (nincs argumentuma)

    int *(*l)(); //l egy függvénymutató, ami egy egészre mutató mutatót visszaadó argumentum nélküli függvényre mutat

    int (*v(int c))(int a, int b);  //v egy függvény, aminek egy egész argmentuma van,
                                    //és egy függvénymutatót ad vissza egy függvényre,
                                    //aminek két egész argumentuma van, (vajon meg lehet nevezni őket fgv pointer típusnévben???)
                                    //és egészet ad vissza

    int (*(*z)(int))(int, int);     //

    return 0;
}
