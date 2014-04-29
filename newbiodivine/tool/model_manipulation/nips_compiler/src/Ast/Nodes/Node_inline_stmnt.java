package Ast.Nodes;

public class Node_inline_stmnt extends Node
{
  private String Attr_line;
  private String Attr_name;
  private String Attr_column;

  public Node_inline_stmnt( String Attr_line, String Attr_name, String Attr_column )
  {
    this.Attr_line = Attr_line;
    this.Attr_name = Attr_name;
    this.Attr_column = Attr_column;
  }

  public Node duplicate( )
  {
    return new Node_inline_stmnt( Attr_line, Attr_name, Attr_column );
  }

  public String getName( )
  {
    return "inline-stmnt";
  }

  public String getAttr_line( )
  {
    return Attr_line;
  }

  public String getAttr_name( )
  {
    return Attr_name;
  }

  public String getAttr_column( )
  {
    return Attr_column;
  }

  public String[][] getAttrs( )
  {
    String[][] attrs = new String[3][2];
    attrs[0][0] = "line";
    attrs[0][1] = Attr_line;
    attrs[1][0] = "name";
    attrs[1][1] = Attr_name;
    attrs[2][0] = "column";
    attrs[2][1] = Attr_column;
    return attrs;
  }

  public void accept( Visitor visitor )
  {
    visitor.visitNode_inline_stmnt( this );
  }
}
