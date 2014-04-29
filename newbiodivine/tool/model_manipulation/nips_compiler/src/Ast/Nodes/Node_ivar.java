package Ast.Nodes;

public class Node_ivar extends Node
{
  private String Attr_line;
  private String Attr_array_size;
  private String Attr_name;
  private String Attr_column;

  public Node_ivar( String Attr_line, String Attr_array_size, String Attr_name, String Attr_column )
  {
    this.Attr_line = Attr_line;
    this.Attr_array_size = Attr_array_size;
    this.Attr_name = Attr_name;
    this.Attr_column = Attr_column;
  }

  public Node duplicate( )
  {
    return new Node_ivar( Attr_line, Attr_array_size, Attr_name, Attr_column );
  }

  public String getName( )
  {
    return "ivar";
  }

  public String getAttr_line( )
  {
    return Attr_line;
  }

  public String getAttr_array_size( )
  {
    return Attr_array_size;
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
    String[][] attrs = new String[4][2];
    attrs[0][0] = "line";
    attrs[0][1] = Attr_line;
    attrs[1][0] = "array-size";
    attrs[1][1] = Attr_array_size;
    attrs[2][0] = "name";
    attrs[2][1] = Attr_name;
    attrs[3][0] = "column";
    attrs[3][1] = Attr_column;
    return attrs;
  }

  public void accept( Visitor visitor )
  {
    visitor.visitNode_ivar( this );
  }
}
