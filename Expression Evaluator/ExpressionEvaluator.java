/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.HashMap;

/**
 *
 * @author Apollo
 */
public class ExpressionEvaluator
{

    /**
     * @param args the command line arguments
     * @throws java.io.FileNotFoundException
     * 
     * In functia main se citeste din fisier cate o linie si se executa comenzile respective.
     */
    public static void main(String[] args) throws FileNotFoundException, IOException
    {
        String line, words[], result, string = "";

        Node n;

        HashMap<String, String> ints = new HashMap<>(); //Retine numerele intregi.
        HashMap<String, String> doubles = new HashMap<>();  //Retine numerele double.
        HashMap<String, String> strings = new HashMap<>();  //Retine stringurile.

        PrintWriter writer;

        try (FileInputStream is = new FileInputStream("arbore.in"))
        {
            BufferedReader reader = new BufferedReader(new InputStreamReader(is));

            writer = new PrintWriter("arbore.out");

            while ((line = reader.readLine()) != null)
            {
                words = line.trim().split(" ");

                if (words[0].equals("int"))
                {
                    ints.put(words[1], words[3].trim().split(";")[0]);

                    continue;
                }

                if (words[0].equals("double"))
                {
                    doubles.put(words[1], words[3].trim().split(";")[0]);

                    continue;
                }

                if (words[0].equals("string"))
                {
                    for (int i = 3; i < words.length; i++)
                    {
                        string += words[i] + " ";
                    }

                    strings.put(words[1], string.trim().split("\"")[1]);

                    string = "";    //Se reseteaza stringul dupa fiecare citire.

                    continue;
                }

                if (words[0].equals("eval"))
                {
                    words[words.length - 1] = words[words.length - 1].trim().split(";")[0];

                    Calculator c = new Calculator();

                    Evaluate visitor = new Evaluate();

                    n = c.returnExpressionTree(words, ints, doubles, strings);
                    
                    c.initialize(n, ints, doubles, strings);

                    //result = c.evaluate(n, ints, doubles, strings);
                    result = c.accept(visitor);

                    if (result.contains("vid"))
                    {
                        result = result.substring(3, result.length());
                    }

                    if (doubles.get(result) != null)
                    {
                        if (n.info.length() - n.info.indexOf(".") >= 3) //In caz ca sunt mai mult de doua zecimale.
                        {
                            writer.printf("%.2f", Double.parseDouble((String) doubles.get(result)));
                        } else
                        {
                            writer.printf("%.1f", Double.parseDouble((String) doubles.get(result)));
                        }

                        continue;
                    }

                    writer.print(result);
                }
            }
        }

        writer.println();

        writer.close();
    }
}
