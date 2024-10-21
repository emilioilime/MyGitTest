#include <iostream>
#include <fstream>
#include <cmath> // 包含 pow() 函数
#include <stack>  // 引入栈头文件
#include <string>
using namespace std;

class SymbolTable {
public:
    SymbolTable(string A, int B) {
        RamAdd = B;
        Symolname = A;
    }

    int RamAdd;
    string Symolname;
};

// Node class for singly linked list
class Node {
public:
    SymbolTable* symbolTable;  // Pointer to SymbolTable object
    Node* next;  // Pointer to the next node

    // Constructor
    Node(SymbolTable* symbolTable) {
        this->symbolTable = symbolTable;
        this->next = nullptr;
    }
};

// Singly linked list class
class SinglyLinkedList {
public:
    Node* head;  // Pointer to the first node

    // Constructor
    SinglyLinkedList() {
        head = nullptr;
    }

    // Insert a new SymbolTable node at the end of the list
    void insert(string A, int B) {
        SymbolTable* newSymbol = new SymbolTable(A, B);
        Node* newNode = new Node(newSymbol);

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Search for a node by Symolname and return the corresponding RamAdd
    int findBySymolname(string s1) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->symbolTable->Symolname == s1) {
                return temp->symbolTable->RamAdd;  // Return RamAdd if match found
            }
            temp = temp->next;
        }
        return -1;  // Return -1 if no match found
    }

    // Display all nodes in the list
    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << "Symbol: " << temp->symbolTable->Symolname << ", Address: " << temp->symbolTable->RamAdd << endl;
            temp = temp->next;
        }
    }

    // Destructor to free memory
    ~SinglyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current->symbolTable;
            delete current;
            current = next;
        }
    }
};




void printArrayUntilNewline(char arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == '\n') {
            break;  // 遇到 '\n' 时终止循环
        }
        cout << arr[i];  // 输出字符
    }
    cout << endl;  // 输出结束后换行
}
void clearArray(char name[], int size) {
    for (int i = 0; i < size; ++i) {
        name[i] = '\0';  // 将每个元素设置为'\0'
    }
}
void output0(ofstream &tmp){
    char ch='0';
    tmp.write(reinterpret_cast<char*>(&ch), sizeof(ch));
    tmp.flush();
    
}
void output1(ofstream &tmp){
    char ch='1';
    tmp.write(reinterpret_cast<char*>(&ch), sizeof(ch));
    tmp.flush();
}
void outputLinebreaks(ofstream &tmp){
    char ch='\n';
    tmp.write(reinterpret_cast<char*>(&ch), sizeof(ch));
    tmp.flush();//立即把缓冲区数据写入文件
}
void Ainstruction(char instruction[],int arrsize,ofstream &tmp){
    output0(tmp);//输出 A 指令最高的 0
    //instruction数组内从第二个元素起存十进制数字的各位，首先得知道这个十进制数字总共有多少位（\0为数组结尾）
    int i=0;
    while(instruction[i]!='\0'){
        i++;
    }//i 就是当前数的位数
    i--;
    int num=0,j=1;
    //构成一个十进制数num=@后的数字  假设有 3 位
    while (i!=0) {
        num=num+(int)(instruction[j]-48)*pow(10,i-1);
        j++;
        i--;
    }
    //将该数转化为二进制数保存并输出
    stack<int> s;  // 定义一个存储整数的栈
        // 向栈中添加元素
    
    while ( num!=0 ) {
            s.push(num%2);
            num=num/2;
    }
    
    //根据栈中元素确定要填充多少个 0
    //有 15 位 栈
    //补的 0 个数是15-s.size()
    for (int i=0; i!=(15-s.size()); i++) {
        output0(tmp);
    }
    // 输出并移除栈的元素
        while (!s.empty()) {
           //栈顶写入文件中
            if(s.top()==1) {
                output1(tmp);
            }else
            {
                output0(tmp);
            }
            s.pop();  // 移除栈顶元素
        }
    //输出结束
    outputLinebreaks(tmp);

}
int compare_compArr(char compArr[]){
    if(compArr[0]=='0'&&compArr[1]=='\0'&&compArr[2]=='\0')
        return 101010;
    else if (compArr[0]=='1'&&compArr[1]=='\0'&&compArr[2]=='\0')
        return 111111;
    else if (compArr[0]=='-' && compArr[1]=='1' && compArr[2]=='\0')
        return 111010;
    else if (compArr[0]=='D' && compArr[1]=='\0' && compArr[2]=='\0')
        return 1100;
    else if (compArr[0]=='A' && compArr[1]=='\0' && compArr[2]=='\0')
        return 110000;
    else if (compArr[0]=='M' && compArr[1]=='\0' && compArr[2]=='\0')
        return 110000;
    else if (compArr[0]=='!' && compArr[1]=='D' && compArr[2]=='\0')
        return 1101;
    else if (compArr[0]=='!' && compArr[1]=='A' && compArr[2]=='\0')
        return 110001;
    else if (compArr[0]=='!' && compArr[1]=='M' && compArr[2]=='\0')
        return 110001;
    else if (compArr[0]=='-' && compArr[1]=='D' && compArr[2]=='\0')
        return 1111;
    else if (compArr[0]=='-' && compArr[1]=='A' && compArr[2]=='\0')
        return 110011;
    else if (compArr[0]=='-' && compArr[1]=='M' && compArr[2]=='\0')
        return 110011;
    else if (compArr[0]=='D' && compArr[1]=='+' && compArr[2]=='1')
        return 11111;
    else if (compArr[0]=='A' && compArr[1]=='+' && compArr[2]=='1')
        return 110111;
    else if (compArr[0]=='M' && compArr[1]=='+' && compArr[2]=='1')
        return 110111;
    else if (compArr[0]=='D' && compArr[1]=='-' && compArr[2]=='1')
        return 1110;
    else if (compArr[0]=='A' && compArr[1]=='-' && compArr[2]=='1')
        return 110010;
    else if (compArr[0]=='M' && compArr[1]=='-' && compArr[2]=='1')
        return 110010;
    else if (compArr[0]=='D' && compArr[1]=='+' && compArr[2]=='A')
        return 10;
    else if (compArr[0]=='D' && compArr[1]=='+' && compArr[2]=='M')
        return 10;
    else if (compArr[0]=='D' && compArr[1]=='-' && compArr[2]=='A')
        return 10011;
    else if (compArr[0]=='D' && compArr[1]=='-' && compArr[2]=='M')
        return 10011;
    else if (compArr[0]=='A' && compArr[1]=='-' && compArr[2]=='D')
        return 111;
    else if (compArr[0]=='M' && compArr[1]=='-' && compArr[2]=='D')
        return 111;
    else if (compArr[0]=='D' && compArr[1]=='&' && compArr[2]=='A')
        return 0;
    else if (compArr[0]=='D' && compArr[1]=='&' && compArr[2]=='M')
        return 0;
    else if (compArr[0]=='D' && compArr[1]=='|' && compArr[2]=='A')
        return 10101;
    else if (compArr[0]=='D' && compArr[1]=='|' && compArr[2]=='M')
        return 10101;
    else
       return 0;
}//错误才传回 0
//c 指令的 4 种情况 分别要确定 3 个部分
void df(char instruction[],ofstream &tmp){//有等有分
//开始 comp 指令打印
    //识别comp指令
    //将识别出来的comp指令存到一个 3 元素数组中
    char compArr[3] = {'\0', '\0', '\0'};
    //清空 compArr保存\0
    
    int i=0 ;//标号
    //先让i指向 instruction 中 等于号 后一个元素
    while(instruction[i++]!='=');
    //现在准备存入compArr 直到遇到';'
    for (int k=0,h=i; instruction[h]!=';'; k++,h++) {
        compArr[k]=instruction[h];
    }
    //compArr已经存入指令
    
    //识别 a  是否是 A 还是 M ? 怎么识别  看 comp 指令中是 A 还是 M
    int AMflag=0;//=1说明是 M 否则默认是 A
    for (int i=0; i<3; i++) {
        if (compArr[i]=='M') {
            AMflag=1;
        }
    }
    if (AMflag==1)
        output1(tmp);
    else
        output0(tmp);
    
    
    //将compArr 跟指令相匹配  确定 comp 的二进制数
    int num=compare_compArr(compArr),g=5;//传命令 回c1c2c3c4c5c6组成的十进制数  （ 如 指令是0 的话就传回 101010 ）
    while (g>=0) {
        int tmpnum1=num/pow(10,g);
        if (tmpnum1==1) {
            output1(tmp);
            num-=pow(10, g);
        }else {
            output0(tmp);
        }
        g--;
    }//输出 comp 指令
    
//开始判断 dest 指令
char destArr[3] = {'\0', '\0', '\0'};
    //加载 desk 指令到 destArr
    int p=0,Aflag=0,Mflag=0,Dflag=0;
    while(instruction[p]!='=')
    {
        destArr[p]=instruction[p];
        p++;
    }
    for (int i=0; i<3; i++) {
        if (destArr[i]=='A')
            Aflag=1;
        else if (destArr[i]=='D')
            Dflag=1;
        else if(destArr[i]=='M')
            Mflag=1;
    }
    //按ADM输出
    if (Aflag==1)
        output1(tmp);
    else
        output0(tmp);
    
    if (Dflag==1)
        output1(tmp);
    else
        output0(tmp);
    
    if (Mflag==1)
        output1(tmp);
    else
        output0(tmp);
    
//开始判断 jump 指令
   //让指针移到;后第二个元素（instruction) 因为跳转指令第一个字母都是 J
    int jump0=0;
    while(instruction[jump0++]!=';');
    jump0++;
    if (instruction[jump0]=='G') {
       
        if (instruction[jump0+1]=='T') {//JGT
            output0(tmp);
            output0(tmp);
            output1(tmp);
            outputLinebreaks(tmp);
        }else if (instruction[jump0+1]=='E'){//JGE
            output0(tmp);
            output1(tmp);
            output1(tmp);
            outputLinebreaks(tmp);
        }
        
    }else if (instruction[jump0]=='E') {//JEQ
        output0(tmp);
        output1(tmp);
        output0(tmp);
        outputLinebreaks(tmp);
    }else if (instruction[jump0]=='L') {
        if (instruction[jump0+1]=='T') {//JLT
            output1(tmp);
            output0(tmp);
            output0(tmp);
            outputLinebreaks(tmp);
        }else if (instruction[jump0+1]=='E'){//JLE
            output1(tmp);
            output1(tmp);
            output0(tmp);
            outputLinebreaks(tmp);
        }
        
    }else if (instruction[jump0]=='N') {//JNE
        output1(tmp);
        output0(tmp);
        output1(tmp);
        outputLinebreaks(tmp);
    }else if (instruction[jump0]=='M'){//JMP
        output1(tmp);
        output1(tmp);
        output1(tmp);
        outputLinebreaks(tmp);
    }
    
   
    
}

void dfx(char instruction[],ofstream &tmp){//无 jump j123=0
    //开始 comp 指令打印
        //识别comp指令
        //将识别出来的comp指令存到一个 3 元素数组中
        char compArr[3] = {'\0', '\0', '\0'};
        //清空 compArr保存\0
        
        int i=0 ;//标号
        //先让i指向 instruction 中 等于号 后一个元素
        while(instruction[i++]!='=');
        //现在准备存入compArr 直到遇到'\0'
        for (int k=0,h=i; instruction[h]!='\0'; k++,h++) {
            compArr[k]=instruction[h];
        }
        //compArr已经存入指令
        
        //识别 a  是否是 A 还是 M ? 怎么识别  看 comp 指令中是 A 还是 M
        int AMflag=0;//=1说明是 M 否则默认是 A
        for (int i=0; i<3; i++) {
            if (compArr[i]=='M') {
                AMflag=1;
            }
        }
        if (AMflag==1)
            output1(tmp);
        else
            output0(tmp);
        
        
        //将compArr 跟指令相匹配  确定 comp 的二进制数
        int num,g=5;
    num=compare_compArr(compArr);
    
    //传命令 回c1c2c3c4c5c6组成的十进制数  （ 如 指令是0 的话就传回 101010 ）
        while (g>=0) {
            int tmpnum1=num/pow(10,g);
            if (tmpnum1==1) {
                output1(tmp);
                num-=pow(10, g);
            }else {
                output0(tmp);
            }
            g--;
        }//输出 comp 指令
        
    //开始判断 dest 指令
    char destArr[3] = {'\0', '\0', '\0'};
        //加载 desk 指令到 destArr
        int p=0,Aflag=0,Mflag=0,Dflag=0;
        while(instruction[p]!='=')
        {
            destArr[p]=instruction[p];
            p++;
        }
        for (int i=0; i<3; i++) {
            if (destArr[i]=='A')
                Aflag=1;
            else if (destArr[i]=='D')
                Dflag=1;
            else if(destArr[i]=='M')
                Mflag=1;
        }
        //按ADM输出
        if (Aflag==1)
            output1(tmp);
        else
            output0(tmp);
        
        if (Dflag==1)
            output1(tmp);
        else
            output0(tmp);
        
        if (Mflag==1)
            output1(tmp);
        else
            output0(tmp);
//输出j1j2j3 都是 0
    output0(tmp);
    output0(tmp);
    output0(tmp);
    outputLinebreaks(tmp);
}
void dxf(char instruction[],ofstream &tmp){//无= d123=0
    //开始 comp 指令打印
        //识别comp指令
        //将识别出来的comp指令存到一个 3 元素数组中
        char compArr[3] = {'\0', '\0', '\0'};
        //清空 compArr保存\0
        
        int i=0 ;//标号
        //让i指向 instruction 中 等于号 后一个元素
        //现在准备存入compArr 直到遇到';'
        for (int k=0,h=i; instruction[h]!=';'; k++,h++) {
            compArr[k]=instruction[h];
        }
        //compArr已经存入指令
        
        //识别 a  是否是 A 还是 M ? 怎么识别  看 comp 指令中是 A 还是 M
        int AMflag=0;//=1说明是 M 否则默认是 A
        for (int i=0; i<3; i++) {
            if (compArr[i]=='M') {
                AMflag=1;
            }
        }
        if (AMflag==1)
            output1(tmp);
        else
            output0(tmp);
        
        
        //将compArr 跟指令相匹配  确定 comp 的二进制数
        int num=compare_compArr(compArr),g=5;//传命令 回c1c2c3c4c5c6组成的十进制数  （ 如 指令是0 的话就传回 101010 ）
        while (g>=0) {
            int tmpnum1=num/pow(10,g);
            if (tmpnum1==1) {
                output1(tmp);
                num-=pow(10, g);
            }else {
                output0(tmp);
            }
            g--;
        }//输出 comp 指令
    //输出desk 3 个 0
    output0(tmp);
    output0(tmp);
    output0(tmp);
    //开始判断 jump 指令
       //让指针移到;后第二个元素（instruction) 因为跳转指令第一个字母都是 J
        int jump0=0;
        while(instruction[jump0++]!=';');
        jump0++;
        if (instruction[jump0]=='G') {
           
            if (instruction[jump0+1]=='T') {//JGT
                output0(tmp);
                output0(tmp);
                output1(tmp);
                outputLinebreaks(tmp);
            }else if (instruction[jump0+1]=='E'){//JGE
                output0(tmp);
                output1(tmp);
                output1(tmp);
                outputLinebreaks(tmp);
            }
            
        }else if (instruction[jump0]=='E') {//JEQ
            output0(tmp);
            output1(tmp);
            output0(tmp);
            outputLinebreaks(tmp);
        }else if (instruction[jump0]=='L') {
            if (instruction[jump0+1]=='T') {//JLT
                output1(tmp);
                output0(tmp);
                output0(tmp);
                outputLinebreaks(tmp);
            }else if (instruction[jump0+1]=='E'){//JLE
                output1(tmp);
                output1(tmp);
                output0(tmp);
                outputLinebreaks(tmp);
            }
            
        }else if (instruction[jump0]=='N') {//JNE
            output1(tmp);
            output0(tmp);
            output1(tmp);
            outputLinebreaks(tmp);
        }else if (instruction[jump0]=='M'){//JMP
            output1(tmp);
            output1(tmp);
            output1(tmp);
            outputLinebreaks(tmp);
        }
    
    
}
void dxfx(char instruction[],ofstream &tmp){//无 jump j123=0 无= d123=0
    //开始 comp 指令打印
        //识别comp指令
        //将识别出来的comp指令存到一个 3 元素数组中
        char compArr[3] = {'\0', '\0', '\0'};
        //清空 compArr保存\0
        
        int i=0 ;//标号
        //让i指向 instruction 中 等于号 后一个元素
        //现在准备存入compArr 直到遇到'\0'
        for (int k=0,h=i; instruction[h]!='\0'; k++,h++) {
            compArr[k]=instruction[h];
        }
        //compArr已经存入指令
        
        //识别 a  是否是 A 还是 M ? 怎么识别  看 comp 指令中是 A 还是 M
        int AMflag=0;//=1说明是 M 否则默认是 A
        for (int i=0; i<3; i++) {
            if (compArr[i]=='M') {
                AMflag=1;
            }
        }
        if (AMflag==1)
            output1(tmp);
        else
            output0(tmp);
        
        
        //将compArr 跟指令相匹配  确定 comp 的二进制数
        int num=compare_compArr(compArr),g=5;//传命令 回c1c2c3c4c5c6组成的十进制数  （ 如 指令是0 的话就传回 101010 ）
        while (g>=0) {
            int tmpnum1=num/pow(10,g);
            if (tmpnum1==1) {
                output1(tmp);
                num-=pow(10, g);
            }else {
                output0(tmp);
            }
            g--;
        }//输出 comp 指令
    output0(tmp);
    output0(tmp);
    output0(tmp);
    output0(tmp);
    output0(tmp);
    output0(tmp);
    outputLinebreaks(tmp);
}

void Cinstruction(char instruction[],int arrsize,ofstream &tmp){
   //首先打印 3 个 1
    output1(tmp);
    output1(tmp);
    output1(tmp);
    int dengyu=0, fenhao=0;//等于和分号的标志位
    for (int i=0; i!=100; i++) {
        if(instruction[i]=='=')
            dengyu=1;
        else if(instruction[i]==';')
            fenhao=1;
    }
    if (dengyu==1) {
        if (fenhao==1) {
            df(instruction,tmp);  //有等有分
        } else {
            dfx(instruction,tmp);  //有等无分 函数命名fx代表没分 f代表有
        }
    }else{
        if (fenhao==1) {
            dxf(instruction,tmp);  //无等有分
        } else {
            dxfx(instruction,tmp);  //无等无分
        }
    }
    
    //有无 jump？  有无=？  四种情况
    
    
    
    //最后补换行
   
}

void RemoveComment(){
    ifstream file1("/Users/emilio/MyCode/FundamentalTestLearningCode/IOfileorgin.asm", ios_base::in | ios_base::binary);
    ofstream file2("/Users/emilio/MyCode/FundamentalTestLearningCode/IOfile.asm", ios_base::binary);//保存  1.删除所有空格2.删除注释和空行 删除注释和空行的中间体，最后一行会是空白
    
    ifstream file("/Users/emilio/MyCode/FundamentalTestLearningCode/IOfile.asm", ios_base::in | ios_base::binary);
    ofstream fileout("/Users/emilio/MyCode/FundamentalTestLearningCode/IOfileclear.asm", ios_base::binary);//保存  1.删除所有空格2.删除注释和空行 删除注释和空行的中间体，最后一行会是空白
    //删除所有空格 碰到啥都输出 除非遇到空格就不输出
    char ch;
    while(file1.get(ch))//此处已经存了当前行 尾部是\0标记
    {
        if(ch!=' ')
            file2.write(reinterpret_cast<char*>(&ch), sizeof(ch));
    }
    
    file1.close();
    file2.close();
    //删除注释和空行
    char name [256];//假设一行文本最多 256 字符
    while(file.getline (name, 256))//此处已经存了当前行 尾部是\0标记
    {
        //输出每一行从开头开始直到碰到两个//字符（连续）  如果是\0那也停止(continue)
        
        //先检测是否空行或者是否以备注开头
        
           //一行的判断输出逻辑
        
        if(    ((name[1]=='/')&&(name[0]=='/') )||name[0]=='\0'   ){//当前行是空行或//开头  什么都不做  不输出
            continue;
        }
        else{
            char ch,n='\n';
            int i=0;
            while(1){//能执行到这说明不是空行或者备注开头  输出每个字符直到遇到终止符(//或\0) 最后加换个行
                ch=name[i];
                
                if(  ((name[i+1]=='/')&&(ch=='/') )||ch=='\0'   ) //判断当前是否是/且后一个字符是否也是/ or是否是\0
                {
                    fileout.write(reinterpret_cast<char*>(&n), sizeof(n));//输出换行
                    break;
                }else{
                    
                    fileout.write(reinterpret_cast<char*>(&ch), sizeof(ch));
                }
                i++;
            }
            
        }
        clearArray(name, 256);
    }
    fileout.close();
    file.close();
}
void RevertTo01(){
    
    ifstream fileclear("/Users/emilio/MyCode/FundamentalTestLearningCode/noSymbol.asm", ios_base::in | ios_base::binary);//无符号无注释版本
    ofstream FinallyTranslateFile("/Users/emilio/MyCode/FundamentalTestLearningCode/FinallyTranslateFile.asm", ios_base::binary);
    
    
    char chararr[256];
    
    while(fileclear.getline (chararr,256)){
        if(chararr[0]=='@')
        {
            Ainstruction(chararr,256,FinallyTranslateFile);
        }else{
            Cinstruction(chararr,256,FinallyTranslateFile);
        }
    }
    fileclear.close();
    FinallyTranslateFile.close();
}
int main() {
    RemoveComment();
 
    //去注释空行完毕
    //创建符号表
    
    SinglyLinkedList list;
        /*示例操作代码
        // Insert some SymbolTable nodes into the list
        list.insert("Symbol1", 100);
        list.insert("Symbol2", 200);
        list.insert("Symbol3", 300);

        // Display the entire list
        cout << "Linked List Contents:" << endl;
        list.display();

        // Search for a Symbol by name and get its RamAdd
        string s1 = "Symbol";
        int ramAdd = list.findBySymolname(s1);//ramAdd 直接返回找到的地址

        if (ramAdd != -1) {
            cout << "\nFound " << s1 << " with RamAdd: " << ramAdd << endl;
        } else {
            cout << "\n" << s1 << " not found in the list." << endl;
        }
        示例操作代码*/
    
    //插入预制表
    list.insert("SP", 0);
    list.insert("LCL", 1);
    list.insert("ARG", 2);
    list.insert("THIS", 3);
    list.insert("THAT", 4);
    // Insert R0-R15
    for (int i = 0; i <= 15; i++) {
        list.insert("R" + to_string(i), i);
    }
    list.insert("SCREEN", 16384);
    list.insert("KBD", 24576);
    
    //第一次扫描文件  将标签符号（以"()"开头结尾）插入符号表 符号和变量只会存在于A指令的@后
    
    //扫描每一行 保存一个当前行数的变量 linenum 如果遇到以()开头的 就存入符号名到链表中去，地址是linenum+1
    ifstream fileclear("/Users/emilio/MyCode/FundamentalTestLearningCode/IOfileclear.asm", ios_base::in | ios_base::binary);//有符号无注释版本
    ofstream  noSymbol("/Users/emilio/MyCode/FundamentalTestLearningCode/noSymbolstep1.asm", ios_base::binary);
    
    //对于标号符号 存的是代表的代码行数 对于变量 存的是地址 标号符号存完后 以一个
    char chararr[256];
    //符号分配是从 16 开始 的  要略过 SCREEN 和 KBD 但是先不管这两个
    int linenum=0;
    while(fileclear.getline (chararr,256)){//取每一行的元素存到 chararr 中去
        
        if(chararr[0]=='(')
        {
            int i=1;
            string symbol,tmp;
            while(chararr[i]!=')'){
                tmp=chararr[i];
                symbol.append(tmp);
                i++;
                //将字符串s添加在本串尾
            }
            list.insert(symbol, linenum+1);//每次循环只存一个 存的是代码中的行数
        }
        linenum++;
    }
    list.display();
    
    fileclear.close();
    noSymbol.close();
    
    //现在开始删除所有标语 所有的标语节点的行号在删除后都得更改 第一个-1 第二个-2 以此类推
    //链表默认有 23 行 从第 24 行开始，修改其Address (修改的都是标记符号）
    
    Node* temp = list.head;
    while (temp != nullptr) {
        if (temp->symbolTable->Symolname != "KBD") {
            temp = temp->next;
        }
    }
    temp = temp->next;//到了第一个标记符号处
    int iii=1;
    while (temp!= nullptr) {//如果当前不是空就修改 然后再下一个节点
        temp->symbolTable->RamAdd = temp->symbolTable->RamAdd-iii;
        iii++;
        temp = temp->next;
    }
    list.display();
    

    
    
    
    
    
    
    
    
    
    //检测A指令,如果不是以数字开头的 说明是符号 但不知道是标签还是变量
    
    
    //第二次扫描文件 如果当前符号不是在链表中则为变量，插入并分配从 16 开始的地址
    
    //将无符号的汇编代码转化为二进制代码
    RevertTo01();

    
    



    return 0;
}
