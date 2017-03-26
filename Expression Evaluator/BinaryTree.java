/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.util.Stack;

/**
 *
 * @author Apollo
 */
public class BinaryTree
{

    String result = "";

    private final Stack<Character> stack = new Stack<>();

    /**
     * @param c
     * @return 
     * 
     * Calculeaza precedenta operatorilor.
     */
    public int prec(char c)
    {
        if (c == '+' || c == '-')
        {
            return 1;
        }
        if (c == '*' || c == '/' || c == '%')
        {
            return 2;
        }

        return 0;
    }

    /**
     * 
     * @param expression
     * @return 
     * 
     * Transforma expresia din forma infixa, in forma postfixa.
     */
    public String infixToPostfix(String expression[])
    {
        int i;

        char c;

        for (i = 1; i < expression.length; i++)
        {
            c = expression[i].charAt(0);

            if (Character.isLetter(c))
            {
                result += " " + expression[i];
            } else if (c == '(')
            {
                stack.push(c);
            } else if (c == ')')
            {
                while (stack.peek() != '(')
                {
                    result += " " + stack.pop();
                }

                stack.pop();    //Se elimina paranteza.
            } else
            {
                while (!stack.isEmpty() && !(stack.peek() == '(') && prec(c) <= prec(stack.peek()))
                {
                    result += " " + stack.pop();
                }

                stack.push(c);
            }
        }

        while (!stack.isEmpty())    //Se adauga la string ce a ramas in stiva.
        {
            result += " " + stack.pop();
        }

        return result;
    }

    /**
     * 
     * @param c
     * @return 
     * 
     * Determina daca inputul este operator sau nu.
     */
    boolean isOperator(char c)
    {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    /**
     * 
     * @param result
     * @return 
     * 
     * Creeaza arborele binar cu expresia in forma postfixa.
     */
    public Node createExpressionTree(String result)
    {
        int i;

        String postfix[] = result.trim().split(" ");

        NodeFactory factory = new NodeFactory();

        Node tree;

        Stack<Node> st = new Stack();

        // Parcurge stringul cu forma postfixa a expresiei.
        for (i = 0; i < postfix.length; i++)
        {
            // Daca e operand, pune-l pe stiva.
            if (!isOperator(postfix[i].charAt(0)))
            {
                tree = factory.returnInstance(postfix[i]);

                st.push(tree);
            } else // Operator.
            {
                tree = factory.returnInstance(postfix[i]);

                // Scoate doua noduri.
                tree.right = st.pop();
                tree.left = st.pop();

                // Pune subexpresia pe stiva.
                st.push(tree);
            }
        }

        tree = st.peek();

        st.pop();

        return tree;
    }
}
