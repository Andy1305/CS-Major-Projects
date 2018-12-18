/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.util.HashMap;

/**
 *
 * @author Apollo
 * 
 * Retine valorile variabilelor si rezultatele expresiilor. 
 */
public class ExprResults
{
    private final HashMap<String, String> vars;

    private static ExprResults instance = null;

    private ExprResults()
    {
        vars = new HashMap<>();
    }

    public HashMap getResults()
    {
        return this.vars;
    }

    public static ExprResults getInstance()
    {
        if(instance == null)
        {
            instance = new ExprResults();
        }

        return instance;
    }
}