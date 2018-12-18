/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Apollo
 */
public class AssignmentEvaluation extends Parser implements Visitable
{

    public String expr, op1, op2;

    public AssignmentEvaluation()
    {

    }

    public AssignmentEvaluation(String expr, String op1, String op2)
    {
        this.expr = expr;
        this.op1 = op1;
        this.op2 = op2;
    }

    @Override
    public void accept(Visitor visitor)
    {
        visitor.visit(this);
    }
}
