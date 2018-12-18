/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Andy
 * 
 * Clasa abstracta pentru Decorator Design pattern.
 */
public abstract class InstructionDecorator implements Instruction
{
    protected Instruction decoratedInstruction;
    
    public InstructionDecorator(Instruction decoratedInstruction)
    {
        this.decoratedInstruction = decoratedInstruction;
    }
    
    @Override
    public int getBracketsPosition(String expr, int index)
    {
        return decoratedInstruction.getBracketsPosition(expr, index);
    }
}
