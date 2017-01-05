//串
// int Index(String S,String T,int pos){
// 	int n,m,i;
// 	String sub;
// 	if(pos>0){
// 		n = StrLength(S);
// 		m = StrLength(T);
// 		i = pos;
// 		while(i<=n-m+1){
// 			SubString(sub,S,i,m);
// 			if(StrCompare(sub,T)!=0){
// 				++i;
// 			}else{
// 				return i;
// 			}
// 		}
// 	}
// 	return 0;
// }



//朴素的模式匹配算法
int Index(String S,String T,int pos){
	int i = pos;
	int j = 1;
	while(i<=S[0]&&j<=T[0]){
		if(S[i]==T[j]){
			++i;
			++j;
		}else{
			i=i-j+2;
			j=1;
		}
	}
	if(j>T[0]){
		return i-T[0];
	}else
		return 0;
}

//KMP算法实现
void get_next(String T,int *next){
	int i,j;
	i = 1;
	j = 0;
	next[1] = 0;
	while(i<T[0]){
		if(j==0||T[i]==T[j]){
			++i;
			++j;
			next[i] = j;
		}else
			j = next[j];
	}
}
int Index_KMP(String S,String T,int pos){
	int i=pos;
	int j = 1;
	int next[255];
	get_next(T,next);
	while(i<=S[0]&&j<=T[0]){
		if(j==0||S[i]==T[j]){
			++i;
			++j;
		}else{
			j=next[j];
		}
	}
	if(j>T[0])
		return i-T[0];
	else
		return 0;
}

//KMP改良
void get_nextval(String T,int *nextval){
	int i,j;
	i=1;
	j=0;
	nextval[1] = 0;
	while(i<T[0]){
		if(j==0||T[i]==T[j]){
			++i;
			++j;
			if(T[i]!=T[j])
				nextval[i] = j;
			else
				nextval[i] = nextval[j];
		}else
			j = nextval[j];
	}

}