package Ast.Nodes;

public class Node_c_state extends Node
{
  private String Attr_string1;
  private String Attr_line;
  private String Attr_column;
  private String Attr_string3;
  private String Attr_string2;

  public Node_c_state( String Attr_string1, String Attr_line, String Attr_column, String Attr_string3, String Attr_string2 )
  {
    this.Attr_string1 = Attr_string1;
    this.Attr_line = Attr_line;
    this.Attr_column = Attr_column;
    this.Attr_string3 = Attr_string3;
    this.Attr_string2 = Attr_string2;
  }

  public Node duplicate( )
  {
    return new Node_c_state( Attr_string1, Attr_line, Attr_column, Attr_string3, Attr_string2 );
  }

  public String getName( )
  {
    return "c-state";
  }

  public String getAttr_string1( )
  {
    return Attr_string1;
  }

  public String getAttr_line( )
  {
    return Attr_line;
  }

  public String getAttr_column( )
  {
    return Attr_column;
  }

  public String getAttr_string3( )
  {
    return Attr_string3;
  }

  public String getAttr_string2( )
  {
    return Attr_string2;
  }

  public String[][] getAttrs( )
  {
    String[][] attrs = new String[5][2];
    attrs[0][0] = "string1";
    attrs[0][1] = Attr_string1;
    attrs[1][0] = "line";
    attrs[1][1] = Attr_line;
    attrs[2][0] = "column";
    attrs[2][1] = Attr_column;
    attrs[3][0] = "string3";
    attrs[3][1] = Attr_string3;
    attrs[4][0] = "string2";
    attrs[4][1] = Attr_string2;
    return attrs;
  }

  public void accept( Visitor visitor )
  {
    visitor.visitNode_c_state( this );
  }
}
