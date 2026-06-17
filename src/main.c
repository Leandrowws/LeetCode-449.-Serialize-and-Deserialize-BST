#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* Inserir(struct TreeNode* root, int val) {
    if(root==NULL) {
        struct TreeNode* aux = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        aux->val = val;
        aux->left = NULL;
        aux->right = NULL;
        return aux;
    } else {
        if(val < root->val) {
            root->left = Inserir(root->left, val);
        } else {
            root->right = Inserir(root->right, val);
        }
        return root;
    }
}

void serializeAux(struct TreeNode* root, char* s, int* i) {
    if(root != NULL) {
        *i += sprintf(s + *i, "%d,", root->val);
        serializeAux(root->left, s, i);
        serializeAux(root->right, s, i);
    }
}

char* serialize(struct TreeNode* root) {
    if(root == NULL) {
        char* s = malloc(1);
        s[0] = '\0';
        return s;
    }
    char* s = malloc(50000);   
    int i = 0;
    serializeAux(root, s, &i);
    s[i] = '\0';
    return s;
}

struct TreeNode* deserialize(char* data) {
    struct TreeNode* root = NULL;
    int i = 0;
    while(data[i] != '\0') {
        int num = 0;
        while(data[i] != ',' && data[i] != '\0') {
            num = num * 10 + (data[i] - '0');
            i++;
        }
        root = Inserir(root, num);
        if(data[i] == ',') {
            i++;
        }
    }
    return root;
}

void Imprimir(struct TreeNode* root) {
    if(root!=NULL) {
        Imprimir(root->left);
        printf("%d ", root->val);
        Imprimir(root->right);
    }
}

int main() {
    struct TreeNode* arv = NULL;
    arv = Inserir(arv, 100);
    arv = Inserir(arv, 150);
    arv = Inserir(arv, 50);
    arv = Inserir(arv, 175);
    arv = Inserir(arv, 25);
    arv = Inserir(arv, 75);
    arv = Inserir(arv, 125);

    Imprimir(deserialize(serialize(arv)));

    return 0;
}
