#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node { 
	int key; 
	struct node *left, *right; 
}Tree;
Tree *root = NULL;

void printGivenLevel(Tree* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->key);
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1);
        printGivenLevel(root->right, level-1);
    }
}

Tree* searching(Tree *root, int aranan){
	if (root == NULL)
		return NULL;
	if (aranan < root->key)
		return searching(root->left, aranan);		
	else if (aranan > root->key)	
		return searching(root->right, aranan);
	else 
		return root;
}

Tree* DegerAl(){
	Tree * yeni;
	yeni = (Tree*) malloc(sizeof(Tree));
	if (yeni == NULL)
	{
		printf("\nBellek dolu...");
		return NULL;
	}

	printf("Elemani Giriniz\n>>");
	scanf("%d", &(yeni->key));
	yeni->right = NULL;
	yeni->left = NULL;
	return yeni;
}

void ekle_rec(Tree *agacroot, Tree *yeni){
	if (root == NULL) root = yeni;
	else{
		if (yeni->key < agacroot->key){
			if (agacroot->left == NULL)
				agacroot->left = yeni;
			else
				ekle_rec(agacroot->left, yeni);
		}
		else{
			if (agacroot->right == NULL)
				agacroot->right = yeni;
			else
				ekle_rec(agacroot->right, yeni);
		}
	}
}

void nodesGreaterThanX(Tree *root, int x)  
{  
    if (root==NULL)  
        return;  
    if (root->key > x)  
        printf("%d ",root->key); 
        
    nodesGreaterThanX(root->left,x); 
    nodesGreaterThanX(root->right,x); 
}   

int getLeafSum(Tree * node) 
{ 
  if(node == NULL)        
    return 0; 
  if(node->left == NULL && node->right==NULL)       
    return node->key;             
  else 
    return getLeafSum(node->left) + getLeafSum(node->right);       
} 

int getLeafCount(Tree * node) 
{ 
  if(node == NULL)        
    return 0; 
  if(node->left == NULL && node->right==NULL)       
    return 1;             
  else 
    return getLeafCount(node->left) + getLeafCount(node->right);       
} 

int aramaAdim(Tree *root, int aranan,int count){
	if (root == NULL)
	{
		return NULL;
	}
	if (aranan < root->key)
	{
		count +=1;
		return aramaAdim(root->left, aranan,count);		
	}

	else if (aranan > root->key)
	{
		count +=1;
		return aramaAdim(root->right, aranan,count);
	}
	else
	{
		count +=1;
		return count;	
	} 
}

int main(){
	Tree *yeni, *bul;
	int key, aranan,choise,adim,level,deger,sayac=0,sum=0,count;
	while (choise != 6){
		printf("\n1-Agaca Eleman Ekleme\n2-Girdiginiz Seviyedeki Elemanlari Bastirma\n3-Arama\n4-Yaprak Dugumlerinin Ortalamasi\n5-Girdiginiz Degerden Buyuk Olanlar\n6-Cikis\n>>");
		scanf("%d",&choise);
		switch (choise){
			case 1:
				yeni = DegerAl();
				ekle_rec(root, yeni);
				break;
			case 2:
					printf("Seviye girin\n>>");
					scanf("%d",&level);
					printGivenLevel(root,level+1);
					break;
			case 3:
				printf("Aranan Eleman\n>>");
				scanf("%d", &aranan);
				if (root != NULL){
					adim = aramaAdim(root, aranan,adim); 
					bul = searching(root, aranan);
					if (bul != NULL)
						printf("%d Elemani %d adimda bulundu.",bul->key,adim);
					else 
						printf("%d Elemani bulunamadi!",aranan);
				}
				else
					printf("\nBos Liste...");
					break;
			case 4:
				sum = getLeafSum(root);
				count = getLeafCount(root);
				printf("Yaprak dugumlerinin ortalamasi: %.2f",float(sum/count));
    			break;
    		case 5:
				printf("Degeri Giriniz\n>>");
				scanf("%d",&deger);
				printf("\n%d degerinden buyuk elemanlar\n",deger);
				nodesGreaterThanX(root,deger);
				break;
			case 6:
				break;
			default:
				break;
		}
	}
}
