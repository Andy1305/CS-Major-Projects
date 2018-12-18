/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Andy
 * 
 * Clasa ce contine metoda care decoreaza metoda getBracketsPosition().
 */
public class ValueInstructionDecorator extends InstructionDecorator
{
    public ValueInstructionDecorator(Instruction decoratedInstruction)
    {
        super(decoratedInstruction);
    }
    
    //Metoda decoratoare.
    public boolean hasBrackets(String str)
    {
        return str.contains("[");
    }
    
    @Override
    public int getBracketsPosition(String expr, int index)
    {
        if(!hasBrackets(expr))
        {
            return -1;
        }
        
        return decoratedInstruction.getBracketsPosition(expr, index);
    }
}
