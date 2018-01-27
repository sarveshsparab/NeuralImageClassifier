#include<stdio.h>
#include<string.h>
float str_cmp(char *str,char *test);
int main(){
    FILE *f_train,*f_wtmat,*f_in,*f_varr,*f_ans;
    char str[120],d[5],symbols[]="012";
    int sym_cnt=strlen(symbols),i,j,k,m,dim=100,zeros;
    f_train=fopen("base_input.txt","r");
    f_wtmat=fopen("wt_mat.txt","w");
    char wt_mat[sym_cnt][100];
    float wm_mat[sym_cnt][100],E=(1.0/dim)/2,v_arr[sym_cnt][1],tmp_prod[sym_cnt][1],tmp_sum;
    int ans_index[sym_cnt];

    for(i=0;i<sym_cnt;i++){
        for(j=0;j<100;j++){
            wt_mat[i][j]=0.0;
        }
    }
    for(i=0;i<sym_cnt;i++){
        for(j=0;j<sym_cnt;j++){
            if(j==i)
                wm_mat[i][j]=1.0;
            else
                wm_mat[i][j]=-1*E;
        }
    }
    k=0;
    while(!feof(f_train)){
        memset(str, '\0', sizeof(str));
        memset(d, '\0', sizeof(d));
        fscanf( f_train , "%s" "%s" , str , d );
        if(symbols[strcspn(symbols,d)]!='\0'){
            fprintf( f_wtmat , "%s\n" , str);
            strcpy(wt_mat[k],str);
            k++;
        }
    }
    fclose(f_train);
    fclose(f_wtmat);
    //********* got wt matrix ***********
    f_in=fopen("test_input.txt","r");
    f_varr=fopen("v_arr.txt","w");
    f_ans=fopen("answers.txt","w");
    m=0;
    while(!feof(f_in)){
        fgets(str,120,f_in);
        fprintf( f_varr , "********** Input No: %d **********\n" , m+1 );
        for(i=0;i<sym_cnt;i++){
            v_arr[i][0]=0.5*str_cmp(str,wt_mat[i])+(float)dim/2;
            fprintf( f_varr , "%f\t" , v_arr[i][0]);
        }
        fprintf( f_varr , "\n" );
        zeros=0;
        while(zeros!=(sym_cnt-1)){
            zeros=0;
            for(i=0;i<sym_cnt;i++){
                for(j=0;j<1;j++){
                    for(k=0;k<sym_cnt;k++){
                        tmp_sum=tmp_sum+wm_mat[i][k]*v_arr[k][j];
                    }
                    tmp_prod[i][j]=tmp_sum;
                    tmp_sum=0;
                }
            }
            for(i=0;i<sym_cnt;i++){
                if(tmp_prod[i][0]<0){
                    tmp_prod[i][0]=0.0;
                    zeros++;
                }
                v_arr[i][0]=tmp_prod[i][0];
            }
            for(i=0;i<sym_cnt;i++){
                fprintf( f_varr , "%f\t" , v_arr[i][0]);
            }
            fprintf( f_varr , "\n" );
        }
        fprintf( f_varr , "\n\n" );
        ans_index[m]=0;
        for(i=0;i<sym_cnt;i++){
            if(v_arr[i][0]>0.000000){
                ans_index[m]=i;
            }
        }
        for(i=0;i<100;i++){
            fprintf( f_ans , "%c" , str[i] );
            if(i%10==9)
                fprintf( f_ans , "\n" );
        }
        fprintf( f_ans , "\nDETECTED SYMBOL ==>> %d\n\n*****************\n" , ans_index[m] );
        m++;
    }
    fclose(f_ans);
    fclose(f_varr);
    fclose(f_in);

    return 0;
}
float str_cmp(char *str,char *test){
    float ans=0;
    int i;
    for(i=0;i<100;i++){
        if(str[i]==test[i])
            ans++;
        else
            ans--;
    }
    return ans;
}
