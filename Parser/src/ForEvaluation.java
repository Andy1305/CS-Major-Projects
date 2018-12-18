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
public class ForEvaluation extends Parser implements Visitable, Instruction
{

    public String expr, expr1, cond, expr2, expr3;

    public ForEvaluation()
    {

    }

    public ForEvaluation(String expr, String expr1, String cond, String expr2, String expr3)
    {
        this.expr = expr;
        this.cond = cond;
        this.expr1 = expr1;
        this.expr2 = expr2;
        this.expr3 = expr3;
    }

    public boolean isNumber(String str)
    {
        return str.matches("[-+]?\\d*\\.?\\d+");
    }

    public int getValue(String str) throws FileNotFoundException
    {
        ExprResults er = ExprResults.getInstance();

        try
        {
            if (isNumber(str))
            {
                return Integer.parseInt(str);
            }
            else
            {

                return Integer.parseInt((String) er.getResults().get(str));
            }
        }
        catch (NumberFormatException e)
        {
            if (str.contains("+") || str.contains("*"))
            {
                ExprEvaluation ee = new ExprEvaluation();

                return ee.evaluate(str);
            }
            
            PrintWriter writer = new PrintWriter((String) er.getResults().get("filename"));
            
            writer.print("Check failed");
            
            writer.close();

            System.exit(0);
        }

        return 0;
    }

    @Override
    public int getBracketsPosition(String expr, int index)
    {
        int i;

        for (i = index; i < expr.length(); i++)
        {
            if (expr.charAt(i) == '[')
            {
                return i;
            }
        }

        return -1;
    }

    //Parseaza si returneaza termenii pe care trebuie sa ii compar/evaluez, in functie de paranteze.
    public int[] evaluateCondition(String cond) throws FileNotFoundException
    {
        int v[] = new int[2], pos;

        String str, tokens[] = cond.trim().split(" ");

        Instruction ins = new ValueInstructionDecorator(new ExprEvaluation());
        
        if (cond.contains("["))
        {
            if (cond.charAt(0) == '<')
            {
                pos = ins.getBracketsPosition(cond, 2);

                if (pos == 2)
                {
                    str = getString(cond, pos);

                    v[0] = evaluateExpr(getString(cond, pos).substring(1, getString(cond, pos).length() - 1));

                    pos = ins.getBracketsPosition(cond, str.length() + 3);
                }
                else
                {
                    str = tokens[1];

                    v[0] = getValue(tokens[1]);

                    pos = ins.getBracketsPosition(cond, tokens[1].length() + 3);
                }

                if (pos > 2)
                {
                    v[1] = evaluateExpr(getString(cond, str.length() + 3).substring(1, getString(cond, str.length() + 3).length() - 1));
                }
                else
                {
                    v[1] = getValue(tokens[2]);
                }
            }

            if (cond.charAt(0) == '=' && cond.charAt(1) == '=')
            {
                pos = ins.getBracketsPosition(cond, 3);

                if (pos == 3)
                {
                    str = getString(cond, pos);

                    v[0] = evaluateExpr(getString(cond, pos).substring(1, getString(cond, pos).length() - 1));

                    pos = ins.getBracketsPosition(cond, str.length() + 4);
                }
                else
                {
                    str = tokens[1];

                    v[0] = getValue(tokens[1]);

                    pos = ins.getBracketsPosition(cond, tokens[1].length() + 4);
                }

                if (pos > 3)
                {
                    v[1] = evaluateExpr(getString(cond, str.length() + 4).substring(1, getString(cond, str.length() + 4).length() - 1));
                }
                else
                {
                    v[1] = getValue(tokens[2]);
                }
            }
        }
        else
        {
            v[0] = getValue(tokens[1]);
            v[1] = getValue(tokens[2]);
        }

        return v;
    }

    @Override
    public void accept(Visitor visitor)
    {
        visitor.visit(this);
    }
}