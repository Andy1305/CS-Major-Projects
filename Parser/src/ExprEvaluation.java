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
public class ExprEvaluation extends Parser implements Instruction
{
    public String expr;
    
    public ExprEvaluation()
    {

    }
    
    public ExprEvaluation(String expr)
    {
        this.expr = expr;
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

    //Returneaza rezultatul unei expresii.
    public int solve(String tokens[]) throws FileNotFoundException
    {
        boolean result;

        switch (tokens[0])
        {
            case "+":
                return getValue(tokens[1]) + getValue(tokens[2]);

            case "*":
                return getValue(tokens[1]) * getValue(tokens[2]);

            case "<":
                result = getValue(tokens[1]) < getValue(tokens[2]);

                if (result == true)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }

            case "==":
                result = getValue(tokens[1]) == getValue(tokens[2]);

                if (result == true)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
        }

        return -1;
    }

    //Parseaza o expresie si ii returneaza rezultatul, cu ajutorul metodei solve().
    public int evaluate(String expr) throws FileNotFoundException
    {
        int pos;

        String tokens[] = expr.trim().split(" ");

        Instruction ins = new ValueInstructionDecorator(new ExprEvaluation());
        
        if (expr.contains("["))
        {
            pos = ins.getBracketsPosition(expr, 2);

            if (pos == 2)
            {
                tokens[1] = Integer.toString(evaluateExpr(getString(expr, pos).substring(1, getString(expr, pos).length() - 1)));
            }

            pos = ins.getBracketsPosition(expr, tokens[1].length() + 3);

            if (pos > 2)
            {
                tokens[2] = Integer.toString(evaluateExpr(getString(expr, tokens[1].length() + 3).substring(1, getString(expr, tokens[1].length() + 3).length() - 1)));
            }
        }

        return solve(tokens);
    }
}