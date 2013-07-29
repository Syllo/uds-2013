void calc_multifor (){
    int i, i2,j,j2;
    multifor(i=1, i2=1; i<N-1, i2<N-1; i++, i2++; 1, 1; 0, 3){
        multifor(j=1, j2=1; j<N-1, j2<N-1; j++, j2++; 1, 1; 0, 0){
            0:  temp[i-1][j-1]=game_of_life(t[i][j],t[i-1][j],t[i-1][j-1],t[i-1][j+1],[i][j-1],[i][j+1],[i+1][j-1],[i+1][j],[i+1][j+1]);
            1:  t[i2][j2]=temp[i2-1][j2-1];
        }
    }
}
