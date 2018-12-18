/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.io.FileNotFoundException;
import java.io.PrintWriter;

/**
 *
 * @author Andy
 * 
 * Evalueaza fiecare expresie in parte, in functie de tipul ei (atribuire, if, for, assert).
 */
public class Evaluator implements Visitor
{

    @Override
    public void visit(AssignmentEvaluation ae)
    {
        ExprResults er = ExprResults.getInstance();

        if (ae.op2.contains("["))
        {
            try
            {
                er.getResults().put(ae.op1, Integer.toString(ae.evaluateExpr(ae.op2.substring(1, ae.op2.length() - 1))));
            }
            catch (FileNotFoundException ex)
            {
                System.out.print("File not found.");
            }
        }
        else
        {
            er.getResults().put(ae.op1, ae.op2);
        }
    }

    @Override
    public void visit(IfEvaluation ie)
    {
        int x = -1, y = -1;

        try
        {
            x = ie.evaluateCondition(ie.cond)[0];
            y = ie.evaluateCondition(ie.cond)[1];
        }
        catch (FileNotFoundException ex)
        {
            System.out.print("Check failed");
        }

        try
        {
            if (ie.cond.charAt(0) == '<')
            {
                if (x < y)
                {
                    ie.evaluateExpr(ie.expr1);
                }
                else
                {
                    ie.evaluateExpr(ie.expr2);
                }
            }
        }
        catch (FileNotFoundException e)
        {
            System.out.print("File not found.");
        }

        try
        {
            if (ie.cond.charAt(0) == '=' && ie.cond.charAt(1) == '=')
            {
                if (x == y)
                {
                    ie.evaluateExpr(ie.expr1);
                }
                else
                {
                    ie.evaluateExpr(ie.expr2);
                }
            }
        }
        catch (FileNotFoundException e)
        {
            System.out.print("File not found.");
        }
    }

    @Override
    public void visit(ForEvaluation fe)
    {
        int x = 0, y = 0;

        try
        {
            fe.evaluateExpr(fe.expr1);
        }
        catch (FileNotFoundException ex)
        {
            System.out.print("File not found.");
        }

        try
        {
            x = fe.evaluateCondition(fe.cond)[0];
            y = fe.evaluateCondition(fe.cond)[1];
        }
        catch (FileNotFoundException ex)
        {
            System.out.print("File not found.");
        }

        if (fe.cond.charAt(0) == '<')
        {
            while (x < y)
            {
                try
                {
                    fe.evaluateExpr(fe.expr3);  //instructiune de executat in for
                    fe.evaluateExpr(fe.expr2);  //incrementare
                }
                catch (FileNotFoundException ex)
                {
                    System.out.print("File not found.");
                }

                try
                {
                    x = fe.evaluateCondition(fe.cond)[0];
                    y = fe.evaluateCondition(fe.cond)[1];
                }
                catch (FileNotFoundException ex)
                {
                    System.out.print("File not found.");
                }
            }
        }

        if (fe.cond.charAt(0) == '=' && fe.cond.charAt(1) == '=')
        {
            while (x == y)
            {
                try
                {
                    fe.evaluateExpr(fe.expr3);
                    fe.evaluateExpr(fe.expr2);

                    x = fe.evaluateCondition(fe.cond)[0];
                    y = fe.evaluateCondition(fe.cond)[1];
                }
                catch (FileNotFoundException ex)
                {
                    System.out.print("File not found.");
                }
            }
        }
    }

    @Override
    public void visit(AssertEvaluation ae)
    {
        int x = 0, y = 0;

        ExprResults er = ExprResults.getInstance();

        PrintWriter writer;

        try
        {
            x = ae.evaluateAssert()[0];
            y = ae.evaluateAssert()[1];
        }
        catch (FileNotFoundException ex)
        {
            System.out.print("File not found.");
        }

        if (ae.cond.charAt(0) == '<')
        {
            if (x >= y)
            {
                if (!ae.expr.contains("return"))
                {
                    try
                    {
                        writer = new PrintWriter((String) er.getResults().get("filename"));

                        ae.checkIfReturnThrowsCheckFailed(ae.expr);

                        writer.print("Missing return");

                        writer.close();

                        System.exit(0);
                    }
                    catch (FileNotFoundException ex)
                    {
                        System.out.print("File not found.");
                    }
                }

                try
                {
                    writer = new PrintWriter((String) er.getResults().get("filename"));

                    writer.print("Assert failed");

                    writer.close();

                    System.exit(0);
                }
                catch (FileNotFoundException ex)
                {
                    System.out.print("File not found");
                }
            }
        }

        if (ae.cond.charAt(0) == '=' && ae.cond.charAt(1) == '=')
        {
            if (x != y)
            {
                if (!ae.expr.contains("return"))
                {
                    try
                    {
                        writer = new PrintWriter((String) er.getResults().get("filename"));
                        
                        ae.checkIfReturnThrowsCheckFailed(ae.expr);

                        writer.print("Missing return");

                        writer.close();

                        System.exit(0);
                    }
                    catch (FileNotFoundException ex)
                    {
                        System.out.print("File not found.");
                    }

                }
                try
                {
                    writer = new PrintWriter((String) er.getResults().get("filename"));

                    writer.print("Assert failed");

                    writer.close();

                    System.exit(0);
                }
                catch (FileNotFoundException ex)
                {
                    System.out.print("File not found.");
                }
            }
        }
    }
}
