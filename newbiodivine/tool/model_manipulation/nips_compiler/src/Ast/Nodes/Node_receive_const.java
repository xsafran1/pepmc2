package Ast.Nodes;

public class Node_receive_const extends Node
{
  private String Attr_line;
  private String Attr_column;
  private String Attr_value;
  private String Attr_neg;

  public Node_receive_const( String Attr_line, String Attr_column, String Attr_value, String Attr_neg )
  {
    this.Attr_line = Attr_line;
    this.Attr_column = Attr_column;
    this.Attr_value = Attr_value;
    this.Attr_neg = Attr_neg;
  }

  public Node duplicate( )
  {
    return new Node_receive_const( Attr_line, Attr_column, Attr_value, Attr_neg );
  }

  public String getName( )
  {
    return "receive-const";
  }

  public String getAttr_line( )
  {
    return Attr_line;
  }

  public String getAttr_column( )
  {
    return Attr_column;
  }

  public String getAttr_value( )
  {
    return Attr_value;
  }

  public String getAttr_neg( )
  {
    return Attr_neg;
  }

  public String[][] getAttrs( )
  {
    String[][] attrs = new String[4][2];
    attrs[0][0] = "line";
    attrs[0][1] = Attr_line;
    attrs[1][0] = "column";
    attrs[1][1] = Attr_column;
    attrs[2][0] = "value";
    attrs[2][1] = Attr_value;
    attrs[3][0] = "neg";
    attrs[3][1] = Attr_neg;
    return attrs;
  }

  public void accept( Visitor visitor )
  {
    visitor.visitNode_receive_const( this );
  }
}
