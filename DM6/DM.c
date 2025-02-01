// #include les machins


int* tables(int n) {
    assert(n >= 6);

    int* ret = malloc(sizeof(int) * 2);
    ret[0] = 0;
    ret[1] = 0;

    int m = n%4;

    if(m == 0) {
        ret[0] = (int) n/4;
    }
    else if(m == 1) {
        ret[0] = ((int) n/4) + 1;
        ret[1] = -1;
    }
    else if(m == 2) {
        ret[0] = ((int) n/4) + 2;
        ret[1] = -2;
    }
    else if(m == 3) {
        ret[0] = ((int) n/4);
        ret[1] = 1;
    }

    return ret;
}