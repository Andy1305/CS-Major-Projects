/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.util.HashMap;

/**
 *
 * @author Apollo
 */
public class Evaluate implements Visitor
{
    /**
     * 
     * @param n
     * @param ints
     * @param doubles
     * @param strings
     * @return 
     * 
     * Metoda parcurge arborele ce contine expresia si calculeaza si evalueaza fiecare nod, pana cand ajunge la rezultatul final, pe care-l returneaza ca string.
     */
    @Override
    public String visit(Node n, HashMap ints, HashMap doubles, HashMap strings)
    {
        if (n == null)
        {
            return null;
        }

        if (n.left == null && n.right == null)
        {
            return n.info;
        } else
        {
            if (Calculator.isOperator(n.info.charAt(0)))
            {
                if (!Calculator.isOperator(n.left.info.charAt(0)) && !Calculator.isOperator(n.right.info.charAt(0)))
                {
                    switch (n.info.charAt(0))
                    {
                        case '+':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '+', ints, doubles, strings);

                            break;

                        case '-':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '-', ints, doubles, strings);

                            break;

                        case '*':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '*', ints, doubles, strings);

                            break;

                        case '/':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '/', ints, doubles, strings);

                            break;
                    }
                }

                if (Calculator.isOperator(n.left.info.charAt(0)) && !Calculator.isOperator(n.right.info.charAt(0)))
                {
                    visit(n.left, ints, doubles, strings);

                    switch (n.info.charAt(0))
                    {
                        case '+':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '+', ints, doubles, strings);

                            break;

                        case '-':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '-', ints, doubles, strings);

                            break;

                        case '*':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '*', ints, doubles, strings);

                            break;

                        case '/':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '/', ints, doubles, strings);

                            break;
                    }
                }
                if (!Calculator.isOperator(n.left.info.charAt(0)) && Calculator.isOperator(n.right.info.charAt(0)))
                {
                    visit(n.right, ints, doubles, strings);

                    switch (n.info.charAt(0))
                    {
                        case '+':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '+', ints, doubles, strings);

                            break;

                        case '-':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '-', ints, doubles, strings);

                            break;

                        case '*':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '*', ints, doubles, strings);

                            break;

                        case '/':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '/', ints, doubles, strings);

                            break;
                    }
                }

                if (Calculator.isOperator(n.left.info.charAt(0)) && Calculator.isOperator(n.right.info.charAt(0)))
                {
                    visit(n.left, ints, doubles, strings);
                    visit(n.right, ints, doubles, strings);

                    switch (n.info.charAt(0))
                    {
                        case '+':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '+', ints, doubles, strings);

                            break;

                        case '-':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '-', ints, doubles, strings);

                            break;

                        case '*':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '*', ints, doubles, strings);

                            break;

                        case '/':
                            n.info = Calculator.calculate(n.left.info, n.right.info, '/', ints, doubles, strings);

                            break;
                    }
                }
            }
        }

        return n.info;
    }
}
