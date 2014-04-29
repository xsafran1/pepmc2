package Ast.Nodes;

public class Node_const_expr extends Node_expr
{
  private String Attr_line;
  private String Attr_column;
  private String Attr_value;

  public Node_const_expr( String Attr_line, String Attr_column, String Attr_value )
  {
    this.Attr_line = Attr_line;
    this.Attr_column = Attr_column;
    this.Attr_value = Attr_value;
  }

  public Node duplicate( )
  {
    return new Node_const_expr( Attr_line, Attr_column, Attr_value );
  }

  public String getName( )
  {
    return "const-expr";
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

  public String[][] getAttrs( )
  {
    String[][] attrs = new String[3][2];
    attrs[0][0] = "line";
    attrs[0][1] = Attr_line;
    attrs[1][0] = "column";
    attrs[1][1] = Attr_column;
    attrs[2][0] = "value";
    attrs[2][1] = Attr_value;
    return attrs;
  }

  public void accept( Visitor visitor )
  {
    visitor.visitNode_const_expr( this );
  }
}
