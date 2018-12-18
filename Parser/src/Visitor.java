/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Andy
 * 
 * Interfata pentru Visitor, particularizata pentru fiecare clasa.
 */
public interface Visitor
{
    public void visit(AssignmentEvaluation ae);
    public void visit(IfEvaluation ie);
    public void visit(ForEvaluation fe);
    public void visit(AssertEvaluation ae);
}