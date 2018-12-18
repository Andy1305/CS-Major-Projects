/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.io.FileNotFoundException;
import java.io.PrintWriter;

/**
 *
 * @author Apollo
 */
public class Parser
{

    private String expr;

    private static Evaluator ev = new Evaluator();

    public Parser()
    {

    }

    public Parser(String expr)
    {
        this.expr = expr;
    }

    //Returneaza un string ce contine expresia pe care vreau sa o parsez/evaluez mai departe.
    public String getString(String expr, int i)
    {
        int count = 0;

        String str = "";

        while (i < expr.length())
        {
            if (expr.contains("["))
            {
                str += expr.charAt(i);

                if (expr.charAt(i) == '[')
                {
                    count++;
                }

                if (expr.charAt(i) == ']')
                {
                    count--;
                }

                if (count == 0)
                {
                    break;
                }
            }
            else
            {
                if (expr.charAt(i) != ' ')
                {
                    str += expr.charAt(i);
                }
                else
                {
                    break;
                }
            }

            i++;
        }

        return str;
    }

    public int evaluateExpr(String expr) throws FileNotFoundException
    {
        int i;

        String expr1, expr2, expr3, cond;

        ExprResults er = ExprResults.getInstance();

        PrintWriter writer;

        for (i = 0; i < expr.length(); i++)
        {
            if (expr.charAt(i) == ';')
            {
                //Reimpart expresia.
                expr1 = getString(expr, i + 2);
                expr2 = getString(expr, i + expr1.length() + 3);

                evaluateExpr(expr1.substring(1, expr1.length() - 1));
                evaluateExpr(expr2.substring(1, expr2.length() - 1));

                i += expr1.length() + expr2.length() + 2;

                return 0;
            }
            else if (expr.charAt(i) == '=')
            {
                //Setez valorile pentru variabile.
                expr1 = getString(expr, i + 2);
                expr2 = getString(expr, i + expr1.length() + 3);

                AssignmentEvaluation ae = new AssignmentEvaluation(this.expr, expr1, expr2);

                i += expr1.length() + expr2.length() + 2;

                ae.accept(ev);

                return 0;
            }
            else if (expr.charAt(i) == 'i' && expr.charAt(i + 1) == 'f')
            {
                //Evaluez iful.
                cond = getString(expr, i + 3);  //conditia
                expr1 = getString(expr, i + cond.length() + 4); //prima parte a conditiei
                expr2 = getString(expr, i + cond.length() + expr1.length() + 5);    //a doua parte a conditiei

                //Elimin parantezele.
                cond = cond.substring(1, cond.length() - 1);
                expr1 = expr1.substring(1, expr1.length() - 1);
                expr2 = expr2.substring(1, expr2.length() - 1);

                IfEvaluation ie = new IfEvaluation(expr, cond, expr1, expr2);

                ie.accept(ev);

                i += cond.length() + expr1.length() + expr2.length() + 6;

                return 0;
            }
            else if (expr.charAt(i) == 'f' && expr.charAt(i + 1) == 'o' && expr.charAt(i + 2) == 'r')
            {
                //Evaluez forul.
                expr1 = getString(expr, i + 4); //initializare
                cond = getString(expr, i + expr1.length() + 5); //conditie
                expr2 = getString(expr, i + expr1.length() + cond.length() + 6);    //incrementare
                expr3 = getString(expr, i + expr1.length() + cond.length() + expr2.length() + 7);   //expresie de evaluat

                expr1 = expr1.substring(1, expr1.length() - 1);
                cond = cond.substring(1, cond.length() - 1);
                expr2 = expr2.substring(1, expr2.length() - 1);
                expr3 = expr3.substring(1, expr3.length() - 1);

                ForEvaluation fe = new ForEvaluation(expr, expr1, cond, expr2, expr3);

                fe.accept(ev);

                i += expr1.length() + cond.length() + expr2.length() + expr3.length() + 9;

                return 0;
            }
            else if (expr.charAt(i) == 'a' && expr.charAt(i + 1) == 's' && expr.charAt(i + 2) == 's' && expr.charAt(i + 3) == 'e' && expr.charAt(i + 4) == 'r' && expr.charAt(i + 5) == 't')
            {
                //Evaluel assertul.
                cond = getString(expr, i + 7);
                cond = cond.substring(1, cond.length() - 1);

                AssertEvaluation ae = new AssertEvaluation(this.expr, cond);

                ae.accept(ev);

                i += cond.length() + 6;

                return 0;
            }
            else if (expr.charAt(i) == 'r' && expr.charAt(i + 1) == 'e' && expr.charAt(i + 2) == 't' && expr.charAt(i + 3) == 'u' && expr.charAt(i + 4) == 'r' && expr.charAt(i + 5) == 'n')
            {
                //Evaluez returnul.
                expr1 = getString(expr, i + 7);

                if (expr1.contains("["))
                {
                    ExprEvaluation ee = new ExprEvaluation(expr);

                    writer = new PrintWriter((String) er.getResults().get("filename"));

                    writer.print(ee.evaluate(expr1.substring(1, expr1.length() - 1)));

                    writer.close();

                    System.exit(0);
                }
                else
                {
                    if (er.getResults().get(expr1) == null)
                    {
                        writer = new PrintWriter((String) er.getResults().get("filename"));

                        writer.print("Check failed");

                        writer.close();

                        System.exit(0);
                    }
                    else
                    {
                        writer = new PrintWriter((String) er.getResults().get("filename"));

                        writer.print(er.getResults().get(expr1));

                        writer.close();

                        return 0;
                    }
                }
            }
            else
            {
                ExprEvaluation ee = new ExprEvaluation();

                expr = expr.trim();

                return ee.evaluate(expr);
            }
        }

        return 0;
    }
}
