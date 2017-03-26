/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import static java.lang.Math.abs;
import java.util.HashMap;

/**
 *
 * @author Apollo
 */
public class Calculator implements Visitable
{

    private String result = "";

    private Node n;

    HashMap<String, String> ints, doubles, strings;

    /**
     *
     * @param n
     * @param ints
     * @param doubles
     * @param strings
     *
     * Initializeaza campurile clasei. Nu am folosit constructor, pentru ca initializarea se face dupa creearea obiectului, in main.
     */
    public void initialize(Node n, HashMap ints, HashMap doubles, HashMap strings)
    {
        this.n = n;

        this.ints = ints;
        this.doubles = doubles;
        this.strings = strings;
    }

    /**
     *
     * @param visitor
     * @return
     *
     * Metoda folosita pentru design pattern-ul Visitor.
     */
    @Override
    public String accept(Visitor visitor)
    {
        return visitor.visit(n, ints, doubles, strings);
    }

    /**
     *
     * @param c
     * @return
     *
     * Determina daca inputul este operator sau nu.
     */
    public static boolean isOperator(char c)
    {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    /**
     *
     * @param var
     * @param ints
     * @param doubles
     * @param strings
     * @return
     *
     * Returneaza tipul variabilei (int, double, String).
     */
    public static int findVariable(String var, HashMap ints, HashMap doubles, HashMap strings)
    {
        if (ints.get(var) != null)
        {
            return 1;
        }

        if (doubles.get(var) != null)
        {
            return 2;
        }

        if (strings.get(var) != null)
        {
            return 3;
        }

        return 0;
    }

    /**
     *
     * @param nr
     * @return
     *
     * Metoda trunchiaza numarul la doua zecimale.
     */
    public static double round(double nr)
    {
        String string = Double.toString(nr);

        int a = string.indexOf(".");

        if (string.length() - a >= 4)
        {
            string = string.substring(0, a + 4);
        }

        return Double.parseDouble(string);
    }

    /**
     *
     * @param op1
     * @param op2
     * @param operator
     * @param ints
     * @param doubles
     * @param strings
     * @return
     *
     * Metoda calculeaza operatia dintre doi termeni si returneaza rezultatul sub forma unui string.
     */
    public static String calculate(String op1, String op2, char operator, HashMap ints, HashMap doubles, HashMap strings)
    {
        if (operator == '+')
        {
            if (findVariable(op1, ints, doubles, strings) == 1)
            {
                int int_op1 = Integer.parseInt((String) ints.get(op1));

                if (findVariable(op2, ints, doubles, strings) == 1) //int + int
                {
                    int int_op2 = Integer.parseInt((String) ints.get(op2));

                    if (ints.get(op1) == null || ints.get(op2) == null)
                    {
                        return "NaN";
                    }

                    ints.put(Integer.toString(int_op1 + int_op2), Integer.toString(int_op1 + int_op2));

                    return Integer.toString(int_op1 + int_op2);
                }

                if (findVariable(op2, ints, doubles, strings) == 2) //int + double
                {
                    double double_op2 = Double.parseDouble((String) doubles.get(op2));

                    if (ints.get(op1) == null || doubles.get(op2) == null)
                    {
                        return "NaN";
                    }

                    doubles.put(Double.toString(round(int_op1 + double_op2)), Double.toString(round(int_op1 + double_op2)));

                    return Double.toString(round(int_op1 + double_op2));
                }

                if (findVariable(op2, ints, doubles, strings) == 3) //int + String
                {
                    strings.put((String) (strings.get(op2)) + int_op1, (String) (strings.get(op2)) + int_op1);

                    return (String) (strings.get(op2)) + int_op1;
                }
            }

            if (findVariable(op1, ints, doubles, strings) == 2)
            {
                double double_op1 = Double.parseDouble((String) doubles.get(op1));

                if (findVariable(op2, ints, doubles, strings) == 1) //double + int
                {
                    int int_op2 = Integer.parseInt((String) ints.get(op2));

                    doubles.put(Double.toString(round(double_op1 + int_op2)), Double.toString(round(double_op1 + int_op2)));

                    return Double.toString(round(double_op1 + int_op2));
                }

                if (findVariable(op2, ints, doubles, strings) == 2) //double + double
                {
                    double double_op2 = Double.parseDouble((String) doubles.get(op2));

                    doubles.put(Double.toString(round(double_op1 + double_op2)), Double.toString(round(double_op1 + double_op2)));

                    return Double.toString(round(double_op1 + double_op2));
                }

                if (findVariable(op2, ints, doubles, strings) == 3) //double + String
                {
                    strings.put((String) (strings.get(op2)) + double_op1, (String) (strings.get(op2)) + double_op1);//

                    return (String) (strings.get(op2)) + double_op1;
                }
            }

            if (findVariable(op1, ints, doubles, strings) == 3)
            {
                if (findVariable(op2, ints, doubles, strings) == 1) //String + int
                {
                    strings.put((String) (strings.get(op1)) + ints.get(op2), (String) (strings.get(op1)) + ints.get(op2));

                    return (String) (strings.get(op1)) + ints.get(op2);
                }

                if (findVariable(op2, ints, doubles, strings) == 2) //String + double
                {
                    strings.put((String) (strings.get(op1)) + doubles.get(op2), (String) (strings.get(op1)) + doubles.get(op2));

                    return (String) (strings.get(op1)) + doubles.get(op2);
                }

                if (findVariable(op2, ints, doubles, strings) == 3) //String + String
                {
                    if (((String) strings.get(op2)).contains("vid"))
                    {
                        strings.put((String) (strings.get(op1)) + ((String) strings.get(op2)).replace("vid", ""), (String) (strings.get(op1)) + ((String) strings.get(op2)).replace("vid", ""));

                        return (String) (strings.get(op1)) + ((String) strings.get(op2)).replace("vid", "");
                    }

                    strings.put((String) (strings.get(op1)) + ((String) strings.get(op2)), (String) (strings.get(op1)) + (String) strings.get(op2));

                    return (String) (strings.get(op1)) + (String) strings.get(op2);
                }
            }
        }

        if (operator == '-')
        {
            if (findVariable(op1, ints, doubles, strings) == 1)
            {
                int int_op1 = Integer.parseInt((String) ints.get(op1));

                if (findVariable(op2, ints, doubles, strings) == 1)
                {
                    int int_op2 = Integer.parseInt((String) ints.get(op2));

                    if (ints.get(op1) == null || ints.get(op2) == null)
                    {
                        return "NaN";
                    }

                    ints.put(Integer.toString(int_op1 - int_op2), Integer.toString(int_op1 - int_op2));

                    return Integer.toString(int_op1 - int_op2);
                }

                if (findVariable(op2, ints, doubles, strings) == 2)
                {
                    double double_op2 = Double.parseDouble((String) doubles.get(op2));

                    if (ints.get(op1) == null || doubles.get(op2) == null)
                    {
                        return "NaN";
                    }

                    doubles.put(Double.toString(round(int_op1 - double_op2)), Double.toString(round(int_op1 - double_op2)));

                    return Double.toString(round(int_op1 - double_op2));
                }

                if (findVariable(op2, ints, doubles, strings) == 3)
                {
                    if (((String) strings.get(op2)).contains("vid"))
                    {
                        ints.put(Integer.toString(int_op1 - 3 - ((String) (strings.get(op2))).length()), Integer.toString(int_op1 - 3 - ((String) (strings.get(op2))).length()));

                        return Integer.toString(int_op1 - 3 - ((String) (strings.get(op2))).length());
                    } else
                    {
                        ints.put(Integer.toString(int_op1 - ((String) (strings.get(op2))).length()), Integer.toString(int_op1 - ((String) (strings.get(op2))).length()));

                        return Integer.toString(int_op1 - ((String) (strings.get(op2))).length());
                    }
                }
            }

            if (findVariable(op1, ints, doubles, strings) == 2)
            {
                double double_op1 = Double.parseDouble((String) doubles.get(op1));

                if (findVariable(op2, ints, doubles, strings) == 1)
                {
                    int int_op2 = Integer.parseInt((String) ints.get(op2));

                    if (doubles.get(op1) == null || ints.get(op2) == null)
                    {
                        return "NaN";
                    }

                    doubles.put(Double.toString(double_op1 - int_op2), Double.toString(double_op1 - int_op2));

                    return Double.toString(double_op1 - int_op2);
                }

                if (findVariable(op2, ints, doubles, strings) == 2)
                {
                    double double_op2 = Double.parseDouble((String) doubles.get(op2));

                    doubles.put(Double.toString(round(double_op1 - double_op2)), Double.toString(round(double_op1 - double_op2)));

                    return Double.toString(round(double_op1 - double_op2));
                }

                if (findVariable(op2, ints, doubles, strings) == 3)
                {
                    if (((String) strings.get(op2)).contains("vid"))
                    {
                        doubles.put(Double.toString(round(double_op1 - 3 - ((String) strings.get(op2)).length())), Double.toString(round(double_op1 - 3 - ((String) strings.get(op2)).length())));

                        return Double.toString(round(double_op1 - 3 - ((String) strings.get(op2)).length()));
                    } else
                    {
                        doubles.put(Double.toString(round(double_op1 - ((String) strings.get(op2)).length())), Double.toString(round(double_op1 - ((String) strings.get(op2)).length())));

                        return Double.toString(round(double_op1 - ((String) strings.get(op2)).length()));
                    }
                }
            }

            if (findVariable(op1, ints, doubles, strings) == 3)
            {
                if (findVariable(op2, ints, doubles, strings) == 1) //String - Int
                {
                    int int_op2 = Integer.parseInt((String) ints.get(op2));

                    if (((String) strings.get(op1)).length() >= int_op2)
                    {
                        if (int_op2 >= 0)
                        {
                            if (((String) strings.get(op1)).contains("vid"))
                            {
                                strings.put(((String) strings.get(op1)).substring(3, ((String) strings.get(op1)).length() - int_op2), ((String) strings.get(op1)).substring(3, ((String) strings.get(op1)).length() - int_op2));

                                return ((String) strings.get(op1)).substring(3, ((String) strings.get(op1)).length() - int_op2);
                            } else
                            {
                                strings.put(((String) strings.get(op1)).substring(0, ((String) strings.get(op1)).length() - int_op2), ((String) strings.get(op1)).substring(0, ((String) strings.get(op1)).length() - int_op2));

                                return ((String) strings.get(op1)).substring(0, ((String) strings.get(op1)).length() - int_op2);
                            }
                        }

                        if (int_op2 < 0)
                        {
                            String mul = "";

                            for (int i = 0; i < abs(int_op2); i++)
                            {
                                mul += '#';
                            }

                            strings.put((String) strings.get(op1) + mul, (String) strings.get(op1) + mul);

                            return (String) strings.get(op1) + mul;
                        }
                    }

                    if (((String) strings.get(op1)).length() < int_op2)
                    {
                        strings.put("NaN", "NaN");

                        return "NaN";   //Sirul vid
                    }
                }

                if (findVariable(op2, ints, doubles, strings) == 2) //String - Double
                {
                    double double_op2 = Double.parseDouble((String) doubles.get(op2));

                    if (op1.equals("NaN") || op2.equals("NaN"))
                    {
                        strings.put("NaN", "NaN");

                        return "NaN";
                    }
                    if (((String) strings.get(op1)).contains("vid"))
                    {
                        int a = ((String) strings.get(op1)).lastIndexOf(".");

                        if (((String) strings.get(op1)).length() - a >= 3)
                        {
                            int b = ((String) strings.get(op1)).length() - a - 3;

                            doubles.put(Double.toString(round(((String) strings.get(op1)).length() - b - 3 - double_op2)), Double.toString(round((((String) strings.get(op1)).length()) - b - 3 - double_op2)));

                            return Double.toString(round(((String) strings.get(op1)).length() - b - 3 - double_op2));
                        }

                        doubles.put(Double.toString(round(((String) strings.get(op1)).length() - 3 - double_op2)), Double.toString(round((((String) strings.get(op1)).length()) - 3 - double_op2)));

                        return Double.toString(round(((String) strings.get(op1)).length() - 3 - double_op2));
                    } else
                    {
                        doubles.put(Double.toString(round(((String) strings.get(op1)).length() - double_op2)), Double.toString(round((((String) strings.get(op1)).length()) - double_op2)));

                        return Double.toString(round(((String) strings.get(op1)).length() - double_op2));
                    }
                }

                if (findVariable(op2, ints, doubles, strings) == 3) //String - String
                {
                    if (op1.equals("NaN") || op2.equals("NaN"))
                    {
                        return "NaN";
                    }

                    if (((String) strings.get(op1)).contains("vid") ^ ((String) strings.get(op2)).contains("vid"))
                    {
                        if (((String) strings.get(op1)).contains("vid"))
                        {
                            ints.put(Integer.toString(((String) strings.get(op1)).length() - 3 - ((String) strings.get(op2)).length()), Integer.toString(((String) strings.get(op1)).length() - ((String) strings.get(op2)).length()));

                            return Integer.toString(((String) strings.get(op1)).length() - 3 - ((String) strings.get(op2)).length());
                        }

                        if (((String) strings.get(op2)).contains("vid"))
                        {
                            ints.put(Integer.toString(((String) strings.get(op1)).length() - ((String) strings.get(op2)).length() + 3), Integer.toString(((String) strings.get(op1)).length() - ((String) strings.get(op2)).length()) + 3);

                            return Integer.toString(((String) strings.get(op1)).length() - ((String) strings.get(op2)).length() + 3);
                        }

                    } else
                    {
                        ints.put(Integer.toString(((String) strings.get(op1)).length() - ((String) strings.get(op2)).length()), Integer.toString(((String) strings.get(op1)).length() - ((String) strings.get(op2)).length()));

                        return Integer.toString(((String) strings.get(op1)).length() - ((String) strings.get(op2)).length());
                    }
                }
            }
        }

        if (operator == '*')
        {
            if (findVariable(op1, ints, doubles, strings) == 1) //op1 = int
            {
                int int_op1 = Integer.parseInt((String) ints.get(op1));

                if (findVariable(op2, ints, doubles, strings) == 1) //int * int
                {
                    int int_op2 = Integer.parseInt((String) ints.get(op2));

                    ints.put(Integer.toString(int_op1 * int_op2), Integer.toString(int_op1 * int_op2));

                    return Integer.toString(int_op1 * int_op2);
                }

                if (findVariable(op2, ints, doubles, strings) == 2) //int * double
                {
                    double double_op2 = Double.parseDouble((String) doubles.get(op2));

                    doubles.put(Double.toString(round(int_op1 * double_op2)), Double.toString(round(int_op1 * double_op2)));

                    return Double.toString(round(int_op1 * double_op2));
                }

                if (findVariable(op2, ints, doubles, strings) == 3) //int * string
                {
                    String mul = "";

                    if (int_op1 > 0)
                    {
                        for (int i = 0; i < int_op1; i++)
                        {
                            mul += (String) strings.get(op2);

                            if (mul.contains("vid"))
                            {
                                mul = mul.substring(3, mul.length());
                            }
                        }

                        strings.put(mul, mul);

                        return mul;
                    } else
                    {
                        strings.put("", "vid");

                        return "";
                    }
                }
            }

            if (findVariable(op1, ints, doubles, strings) == 2) //op1 = double
            {
                double double_op1 = Double.parseDouble((String) doubles.get(op1));

                if (findVariable(op2, ints, doubles, strings) == 1)
                {
                    int int_op2 = Integer.parseInt((String) ints.get(op2));

                    doubles.put(Double.toString(round(double_op1 * int_op2)), Double.toString(round(double_op1 * int_op2)));

                    return Double.toString(round(double_op1 * int_op2));
                }

                if (findVariable(op2, ints, doubles, strings) == 2)
                {
                    double double_op2 = Double.parseDouble((String) doubles.get(op2));

                    doubles.put(Double.toString(round(double_op1 * double_op2)), Double.toString(round(double_op1 * double_op2)));

                    return Double.toString(round(double_op1 * double_op2));
                }

                if (findVariable(op2, ints, doubles, strings) == 3)
                {

                    if (((String) strings.get(op2)).contains("vid"))
                    {
                        doubles.put(Double.toString(round(double_op1 * (((String) strings.get(op2)).length() - 3))), Double.toString(round(double_op1 * (((String) strings.get(op2)).length() - 3))));

                        return Double.toString(round(double_op1 * (((String) strings.get(op2)).length() - 3)));
                    } else
                    {
                        doubles.put(Double.toString(round(double_op1 * ((String) strings.get(op2)).length())), Double.toString(round(double_op1 * ((String) strings.get(op2)).length())));

                        return Double.toString(round(double_op1 * ((String) strings.get(op2)).length()));
                    }
                }
            }

            if (findVariable(op1, ints, doubles, strings) == 3) //op1 = string
            {
                if (findVariable(op2, ints, doubles, strings) == 1) //string * int
                {
                    int int_op2 = Integer.parseInt((String) ints.get(op2));

                    String mul = "";

                    if (int_op2 > 0)
                    {
                        for (int i = 0; i < int_op2; i++)
                        {
                            mul += (String) strings.get(op1);

                            if (mul.contains("vid"))
                            {
                                mul = mul.substring(3, mul.length());
                            }
                        }

                        strings.put(mul, mul);

                        return mul;
                    } else
                    {
                        strings.put("", "vid");

                        return "";
                    }
                }

                if (findVariable(op2, ints, doubles, strings) == 2) //string * double
                {
                    double double_op2 = Double.parseDouble((String) doubles.get(op2));

                    if (((String) strings.get(op1)).contains("vid"))
                    {
                        doubles.put(Double.toString(round((((String) strings.get(op1)).length() - 3) * double_op2)), Double.toString(round((((String) strings.get(op1)).length() - 3) * double_op2)));

                        return Double.toString(round((((String) strings.get(op1)).length() - 3) * double_op2));
                    } else
                    {
                        doubles.put(Double.toString(round(((String) strings.get(op1)).length() * double_op2)), Double.toString(round(((String) strings.get(op1)).length() * double_op2)));

                        return Double.toString(round(((String) strings.get(op1)).length() * double_op2));
                    }
                }

                if (findVariable(op2, ints, doubles, strings) == 3) //string * string
                {
                    if ((((String) strings.get(op1)).contains("vid")) ^ (((String) strings.get(op2)).contains("vid")))
                    {
                        if (((String) strings.get(op1)).contains("vid"))
                        {
                            ints.put(Integer.toString((((String) strings.get(op1)).length() - 3) * ((String) strings.get(op2)).length()), Integer.toString((((String) strings.get(op1)).length() - 3) * ((String) strings.get(op2)).length()));

                            return Integer.toString((((String) strings.get(op1)).length() - 3) * ((String) strings.get(op2)).length());
                        }

                        if (((String) strings.get(op2)).contains("vid"))
                        {
                            ints.put(Integer.toString(((String) strings.get(op1)).length() * (((String) strings.get(op2)).length() - 3)), Integer.toString(((String) strings.get(op1)).length() * (((String) strings.get(op2)).length() - 3)));

                            return Integer.toString(((String) strings.get(op1)).length() * (((String) strings.get(op2)).length() - 3));
                        }
                    }

                    if ((((String) strings.get(op1)).contains("vid")) && (((String) strings.get(op2)).contains("vid")))
                    {
                        ints.put(Integer.toString((((String) strings.get(op1)).length() - 3) * (((String) strings.get(op2)).length() - 3)), Integer.toString((((String) strings.get(op1)).length() - 3) * (((String) strings.get(op2)).length() - 3)));

                        return Integer.toString((((String) strings.get(op1)).length() - 3) * (((String) strings.get(op2)).length() - 3));
                    }

                    ints.put(Integer.toString(((String) strings.get(op1)).length() * ((String) strings.get(op2)).length()), Integer.toString(((String) strings.get(op1)).length() * ((String) strings.get(op2)).length()));

                    return Integer.toString(((String) strings.get(op1)).length() * ((String) strings.get(op2)).length());
                }
            }
        }

        if (operator == '/')
        {
            if (findVariable(op1, ints, doubles, strings) == 1)
            {
                int int_op1 = Integer.parseInt((String) ints.get(op1));

                if (findVariable(op2, ints, doubles, strings) == 1) //int / int
                {
                    int int_op2 = Integer.parseInt((String) ints.get(op2));

                    if (int_op2 != 0)
                    {
                        ints.put(Integer.toString(int_op1 / int_op2), Integer.toString(int_op1 / int_op2));

                        return Integer.toString(int_op1 / int_op2);
                    } else
                    {
                        strings.put("NaN", "NaN");

                        return "NaN";
                    }
                }

                if (findVariable(op2, ints, doubles, strings) == 2) //int / double
                {
                    double double_op2 = Double.parseDouble((String) doubles.get(op2));

                    if (double_op2 != 0)
                    {
                        doubles.put(Double.toString(round(int_op1 / double_op2)), Double.toString(round(int_op1 / double_op2)));

                        return Double.toString(round(int_op1 / double_op2));
                    } else
                    {
                        strings.put("NaN", "NaN");

                        return "NaN";
                    }
                }

                if (findVariable(op2, ints, doubles, strings) == 3) //int / string
                {
                    if (((String) strings.get(op2)).length() != 0)
                    {
                        ints.put(Integer.toString(int_op1 / ((String) strings.get(op2)).length()), Integer.toString(int_op1 / ((String) strings.get(op2)).length()));

                        return Integer.toString(int_op1 / ((String) strings.get(op2)).length());
                    } else
                    {
                        strings.put("NaN", "NaN");

                        return "NaN";
                    }
                }
            }

            if (findVariable(op1, ints, doubles, strings) == 2)
            {
                double double_op1 = Double.parseDouble((String) doubles.get(op1));

                if (findVariable(op2, ints, doubles, strings) == 1) //double / int
                {
                    int int_op2 = Integer.parseInt((String) ints.get(op2));

                    if (int_op2 != 0)
                    {
                        doubles.put(Double.toString(round(double_op1 / int_op2)), Double.toString(round(double_op1 / int_op2)));

                        return Double.toString(round(double_op1 / int_op2));
                    } else
                    {
                        strings.put("NaN", "NaN");

                        return "NaN";
                    }
                }

                if (findVariable(op2, ints, doubles, strings) == 2) //double / double
                {
                    double double_op2 = Double.parseDouble((String) doubles.get(op2));

                    if (double_op2 != 0)
                    {
                        doubles.put(Double.toString(round(double_op1 / double_op2)), Double.toString(round(double_op1 / double_op2)));

                        return Double.toString(round(double_op1 / double_op2));
                    } else
                    {
                        strings.put("NaN", "NaN");

                        return "NaN";
                    }
                }

                if (findVariable(op2, ints, doubles, strings) == 3) //double / string
                {
                    if (((String) strings.get(op2)).length() != 0)
                    {
                        doubles.put(Double.toString(round(double_op1 / ((String) strings.get(op2)).length())), Double.toString(round(double_op1 / ((String) strings.get(op2)).length())));

                        return Double.toString(round(double_op1 / ((String) strings.get(op2)).length()));
                    } else
                    {
                        strings.put("NaN", "NaN");

                        return "NaN";
                    }
                }
            }

            if (findVariable(op1, ints, doubles, strings) == 3)
            {
                if (findVariable(op2, ints, doubles, strings) == 1) //string / int
                {
                    int int_op2 = Integer.parseInt((String) ints.get(op2));

                    if (((String) strings.get(op1)).equals("NaN") || int_op2 <= 0)
                    {
                        strings.put((String) strings.get(op1), (String) strings.get(op1));

                        return (String) strings.get(op1);
                    } else
                    {
                        strings.put(((String) strings.get(op1)).substring(0, ((String) strings.get(op1)).length() / int_op2), ((String) strings.get(op1)).substring(0, ((String) strings.get(op1)).length() / int_op2));

                        return ((String) strings.get(op1)).substring(0, ((String) strings.get(op1)).length() / int_op2);
                    }
                }

                if (findVariable(op2, ints, doubles, strings) == 2) //string / double
                {
                    double double_op2 = Double.parseDouble((String) doubles.get(op2));

                    if (double_op2 != 0)
                    {
                        doubles.put(Double.toString(round(((String) strings.get(op1)).length() / double_op2)), Double.toString(round(((String) strings.get(op1)).length() / double_op2)));

                        return Double.toString(round(((String) strings.get(op1)).length() / double_op2));
                    } else
                    {
                        strings.put("NaN", "NaN");

                        return "NaN";
                    }
                }

                if (findVariable(op2, ints, doubles, strings) == 3) //string / string
                {
                    if (((String) strings.get(op2)).length() != 0)
                    {
                        ints.put(Integer.toString(((String) strings.get(op1)).length() / ((String) strings.get(op2)).length()), Integer.toString(((String) strings.get(op1)).length() / ((String) strings.get(op2)).length()));

                        return Integer.toString(((String) strings.get(op1)).length() / ((String) strings.get(op2)).length());
                    } else
                    {
                        strings.put("NaN", "NaN");

                        return "NaN";
                    }
                }
            }
        }

        return null;
    }

    /**
     *
     * @param words
     * @param ints
     * @param doubles
     * @param strings
     * @return
     *
     * Returneaza radacina arborelui.
     */
    public Node returnExpressionTree(String words[], HashMap ints, HashMap doubles, HashMap strings)
    {
        BinaryTree tree = new BinaryTree();

        result = tree.infixToPostfix(words);

        n = tree.createExpressionTree(result);

        return n;
    }
}
