#include "derivative.h"

double derivative::numDeriv(node express, double x) {
    return (express.evaluate(x + (1e-15)) - express.evaluate(x)) / 1e-15;
}

node* derivative::deriv(node &express) {
    switch (express.m_data.tokenType) {
        case token::Constant:
        {
            node* res = new node(token("0"));
            return res;
            break;
        }
        case token::Variable:
        {
            if (express.m_data.tokenString == "x") {
                node* res = new node(token("1"));
                return res;
            }
            node* res = new node(token(express.m_data.tokenString + "'"));
            return res;
            break;
        }
        case token::Operator:
        {
            std::vector<bool> isConst;
            for (int i = 0; i < (int)express.children.size(); i++) {
                if (express.children.at(i)->m_data.tokenType == token::Constant) {
                    isConst.push_back(true);
                }
                else {
                    isConst.push_back(false);
                }
            }

            if (express.m_data.tokenString.compare("+") == 0 || express.m_data.tokenString.compare("-") == 0) {
                node* res = new node(express.m_data);
                node* a = deriv(*express.children.at(0));
                node* b = deriv(*express.children.at(1));
                res->children.push_back(a);
                res->children.push_back(b);
                return res;
            }
            else if (express.m_data.tokenString.compare("*") == 0) {
                node* res;
                if (isConst.at(0) && !isConst.at(1)) {
                    res = new node(token("*"));
                    node* a = new node(express.children.at(0));
                    res->children.push_back(a);
                    node* b = deriv(*express.children.at(1));
                    res->children.push_back(b);
                }
                else if (!isConst.at(0) && isConst.at(1)) {
                    res = new node(token("*"));
                    node* a = deriv(*express.children.at(0));
                    res->children.push_back(a);
                    node* b = new node(express.children.at(1));
                    res->children.push_back(b);
                }
                else {
                    node* a = deriv(*express.children.at(0));
                    node* b = new node(express.children.at(0));
                    node* c = deriv(*express.children.at(1));
                    node* d = new node(express.children.at(1));
                    res = new node(token("+"));
                    node* mult = new node(token("*"));
                    res->children.push_back(mult);
                    res->children.at(0)->children.push_back(b);
                    res->children.at(0)->children.push_back(c);
                    mult = new node(token("*"));
                    res->children.push_back(mult);
                    res->children.at(1)->children.push_back(d);
                    res->children.at(1)->children.push_back(a);
                }
                return res;
            }
            else if (express.m_data.tokenString.compare("/") == 0) {
                if (isConst.at(0) && !isConst.at(1)) {
                    node* res = new node(token("*"));
                    node* divide = new node(token("/"));
                    res->children.push_back(divide);
                    node op1 = node::operate(std::vector<node> {express.children.at(0), node(token("-1"))}, multiply);
                    res->children.at(0)->children.push_back(&op1);
                    node op2 = node::operate(std::vector<node> {express.children.at(1), node(token("2"))}, power);
                    res->children.at(0)->children.push_back(&op2);
                    res->children.push_back(deriv(*express.children.at(1)));
                    return res;
                }
                else if (!isConst.at(0) && isConst.at(1)) {
                    node* res = new node(token("/"));
                    node* a = deriv(*express.children.at(0));
                    node* b = new node(express.children.at(1));
                    res->children.push_back(a);
                    res->children.push_back(b);
                    return res;
                }
                node* res = new node(token("/"));
                node* a = deriv(*express.children.at(0));
                node* b = new node(express.children.at(0));
                node* c = deriv(*express.children.at(1));
                node* d = new node(express.children.at(1));
                node* e = new node(token("2"));
                res->children.push_back(&node(token("-")));
                res->children.at(0)->children.push_back(&node(token("*")));
                res->children.at(0)->children.at(0)->children.push_back(a);
                res->children.at(0)->children.at(0)->children.push_back(d);
                res->children.at(0)->children.push_back(&node(token("*")));
                res->children.at(0)->children.at(1)->children.push_back(b);
                res->children.at(0)->children.at(1)->children.push_back(c);
                res->children.push_back(&node(token("^")));
                res->children.at(1)->children.push_back(d);
                res->children.at(1)->children.push_back(e);
                return res;
            }
            else if (express.m_data.tokenString.compare("^") == 0) {
                if (isConst.at(0) && isConst.at(1)) {
                    node* res = new node(token("0"));
                    return res;
                }
                else if (isConst.at(0)) {
                    node* res = new node(token("*"));
                    node* a = deriv(*express.children.at(1));
                    node* b = new node(express);
                    res->children.at(0)->children.push_back(b);
                    res->children.at(0)->children.push_back(&node(token("ln")));
                    res->children.at(0)->children.at(1)->children.push_back(&express.children.at(1)->copy());
                    res->children.push_back(a);
                    return res;
                }
                else {
                    node* res = new node(token("*"));
                    node* exp = new node(token("^"));
                    node* plus = new node(token("+"));
                    node* mult = new node(token("*"));
                    node* div = new node(token("/"));
                    node* ln = new node(token("ln"));
                    node* a = deriv(*express.children.at(0));
                    node* b = new node(express.children.at(0));
                    node* c = deriv(*express.children.at(1));
                    node* d = new node(express.children.at(1));
                    res->children.push_back(exp);
                    res->children.push_back(new node(token("+")));
                    res->children.at(0)->children.push_back(b);
                    res->children.at(0)->children.push_back(d);
                    res->children.at(1)->children.push_back(mult);
                    mult = new node(token("*"));
                    res->children.at(1)->children.push_back(mult);
                    res->children.at(1)->children.at(0)->children.push_back(c);
                    res->children.at(1)->children.at(0)->children.push_back(ln);
                    res->children.at(1)->children.at(0)->children.at(1)->children.push_back(b);
                    res->children.at(1)->children.at(0)->children.push_back(c);
                    res->children.at(1)->children.at(1)->children.push_back(div);
                    res->children.at(1)->children.at(1)->children.push_back(a);
                    res->children.at(1)->children.at(1)->children.at(0)->children.push_back(d);
                    res->children.at(1)->children.at(1)->children.at(0)->children.push_back(b);
                    return res;
                }
            }
            break;
        }
        case token::Function:
        {
            if (express.children.at(0)->compare(node(token("x")))) {
                node* res = new node(token(express.m_data.tokenString + "'"));
                node* x = new node(token("x"));
                res->children.push_back(x);
                return res;
            }
            node* res = new node(token("*"));
            node* a = deriv(*express.children.at(0));
            res->children.push_back(new node(token(express.m_data.tokenString + "'")));
            res->children.at(0)->children.push_back(&express.children.at(0)->copy());
            res->children.push_back(a);
            break;
        }
        default:
        {
            std::cout << "invalid expression" << std::endl;
            break;
        }
    }
}