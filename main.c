extern void printone(char* c);
int main() {
    char letra = 'A';
    printone(&letra);
    letra = '\n';
    printone(&letra);
    return 0;
}