#include <iostream>
#include <queue>

template<class CL1>
class Node {
	public: CL1 cl1_Field;
	public: Node<CL1>* op_Lt;
	public: Node<CL1>* op_Rt;
    public: Node(){
        op_Lt = nullptr;
        op_Rt = nullptr;
    }
};

template<class CL1>
class Tree{
    public: Node<CL1>* op_Root;
    public: Tree(CL1 cl1_Data){
        op_Root = nullptr;
        op_Root = fn_CreNode(cl1_Data);
    }
    public: ~Tree(){
        fn_TraInOrder(op_Root, true);
    }
    public: Node<CL1>* fn_CreNode(CL1 cl1_Data){
        Node<CL1>* o_NewNode = new Node<CL1>();
        try{
            if (!o_NewNode) {
                throw "Memory allocation error\n";
            }
        }
        catch(const char* cp_Msg){
            std::cout<< cp_Msg;
            exit(1);
        }
        o_NewNode->cl1_Field = cl1_Data;
        return o_NewNode;
    }


    public: void fn_InsNode(CL1 cl1_Data){
        std::queue<Node<CL1>*> o_Qu;
        o_Qu.push(op_Root);

        for (;!o_Qu.empty();) {
            Node<CL1>* op_Tmp = o_Qu.front();
            o_Qu.pop();

            if (op_Tmp->op_Lt != nullptr)
                o_Qu.push(op_Tmp->op_Lt);
            else {
                op_Tmp->op_Lt = fn_CreNode(cl1_Data);
                return;
            }

            if (op_Tmp->op_Rt != nullptr)
                o_Qu.push(op_Tmp->op_Rt);
            else {
                op_Tmp->op_Rt = fn_CreNode(cl1_Data);
                return;
            }
        }
    }

    public: void fn_TraInOrder(Node<CL1>* op_Tmp, bool b_Mode = false){
        if (op_Tmp == nullptr)
            return;

        fn_TraInOrder(op_Tmp->op_Lt, b_Mode);
        Node<CL1>* op_TmpRt = op_Tmp->op_Rt;

        if(b_Mode == false){
            std::cout << op_Tmp->cl1_Field << ' ';
        }
        else{
            delete op_Tmp;
        }
        fn_TraInOrder(op_TmpRt, b_Mode);
    }

    public: void fn_SeaNode(Node<CL1>* op_Tmp, Node<CL1>* op_TmpP, CL1& cl1_Val,
                            Node<CL1>* op_SerN, Node<CL1>* op_SerNP, Node<CL1>* op_Last, Node<CL1>* op_LastP){
        if (op_Tmp == nullptr)
            return;

        fn_SeaNode(op_Tmp->op_Lt, op_Tmp,  cl1_Val, op_SerN, op_SerNP, op_Last, op_LastP);
        if(op_Tmp->cl1_Field == cl1_Val){
            op_SerNP = op_TmpP;
            op_SerN = op_Tmp;
        }
        op_Last = op_Tmp;
        op_LastP = op_Tmp;
        fn_SeaNode(op_Tmp->op_Rt, op_Tmp,  cl1_Val, op_SerN, op_SerNP, op_Last, op_LastP);
    }

    public: void fn_DelNode(Node<CL1>* op_Tmp, CL1& cl1_Val){
        Node<CL1>* op_SerN = nullptr;
        Node<CL1>* op_SerNP = nullptr;
        Node<CL1>* op_Last = nullptr;
        Node<CL1>* op_LastP = nullptr;
        fn_SeaNode(op_Tmp->op_Rt, op_Tmp, cl1_Val, op_SerN, op_SerNP, op_Last, op_LastP);

        if(op_SerN == nullptr){
            return ;
        }

        if(op_SerN->op_Lt ==nullptr && op_SerN->op_Rt ==nullptr){
            if(op_SerNP != nullptr){
                if(op_SerNP->op_Lt == op_SerN){
                    op_SerNP->op_Lt =nullptr;
                }
                else if(op_SerNP->op_Rt == op_SerN){
                    op_SerNP->op_Rt =nullptr;
                }
            }
            delete op_SerN;
        }
        else{
            CL1 cl1_Tmp = op_SerN->cl1_Field;
            op_SerN->cl1_Field = op_Last-> cl1_Field;
            op_Last-> cl1_Field = cl1_Tmp;
            if(op_LastP != nullptr){
                if(op_LastP->op_Lt == op_Last){
                    op_LastP->op_Lt =nullptr;
                }
                else if(op_LastP->op_Rt == op_Last){
                    op_LastP->op_Rt = nullptr;
                }
            }
            delete op_Last;
        }
    }
};

int main(){
    Tree<int> o_Tree(10);
    o_Tree.fn_InsNode(11);
    o_Tree.fn_InsNode(7);
    o_Tree.fn_InsNode(9);
    o_Tree.fn_InsNode(15);
    o_Tree.fn_InsNode(8);

	std::cout << "Inorder traversal before insertion: ";
	o_Tree.fn_TraInOrder(o_Tree.op_Root);
	std::cout << "\n";

	int i_Key = 12;
	o_Tree.fn_InsNode(i_Key);

	std::cout << "Inorder traversal after insertion: ";
	o_Tree.fn_TraInOrder(o_Tree.op_Root);
	std::cout << "\n";

	return 0;
}
