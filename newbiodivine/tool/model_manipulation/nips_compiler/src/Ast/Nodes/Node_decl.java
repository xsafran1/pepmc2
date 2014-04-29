package Ast.Nodes;

public class Node_decl extends Node_step
{
  private String Attr_line;
  private String Attr_column;
  private String Attr_typename;
  private String Attr_visible;

  public Node_decl( String Attr_line, String Attr_column, String Attr_typename, String Attr_visible )
  {
    this.Attr_line = Attr_line;
    this.Attr_column = Attr_column;
    this.Attr_typename = Attr_typename;
    this.Attr_visible = Attr_visible;
  }

  public Node duplicate( )
  {
    return new Node_decl( Attr_line, Attr_column, Attr_typename, Attr_visible );
  }

  public String getName( )
  {
    return "decl";
  }

  public String getAttr_line( )
  {
    return Attr_line;
  }

  public String getAttr_column( )
  {
    return Attr_column;
  }

  public String getAttr_typename( )
  {
    return Attr_typename;
  }

  public String getAttr_visible( )
  {
    return Attr_visible;
  }

  public String[][] getAttrs( )
  {
    String[][] attrs = new String[4][2];
    attrs[0][0] = "line";
    attrs[0][1] = Attr_line;
    attrs[1][0] = "column";
    attrs[1][1] = Attr_column;
    attrs[2][0] = "typename";
    attrs[2][1] = Attr_typename;
    attrs[3][0] = "visible";
    attrs[3][1] = Attr_visible;
    return attrs;
  }

  public void accept( Visitor visitor )
  {
    visitor.visitNode_decl( this );
  }
}
