/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

/**
 *
 * @author Apollo
 */
public class Tema_PP_1
{

    /**
     * @param args the command line arguments
     * @throws java.io.FileNotFoundException
     */
    public static void main(String args[]) throws FileNotFoundException
    {
        String expr = "";

        ExprResults er = ExprResults.getInstance();

        File file = new File(args[0]);

        PrintWriter writer;

        er.getResults().put("filename", args[1]);

        try (Scanner s = new Scanner(file))
        {
            while (s.hasNextLine())
            {
                expr += s.nextLine();
            }
        }

        expr = expr.substring(1, expr.length() - 1);    //Elimin parantezele initiale.

        expr = expr.replaceAll("\\s+", " ");            //Elimin spatiile inutile.

        Parser parser = new Parser(expr);

        parser.evaluateExpr(expr);

        if (!expr.contains("return"))
        {
            writer = new PrintWriter(args[1]);

            writer.print("Missing return");

            writer.close();

            System.exit(0);
        }
    }
}
