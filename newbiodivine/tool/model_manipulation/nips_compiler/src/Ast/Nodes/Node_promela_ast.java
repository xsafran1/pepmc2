package Ast.Nodes;

public class Node_promela_ast extends Node
{
  private String Attr_source;

  public Node_promela_ast( String Attr_source )
  {
    this.Attr_source = Attr_source;
  }

  public Node duplicate( )
  {
    return new Node_promela_ast( Attr_source );
  }

  public String getName( )
  {
    return "promela-ast";
  }

  public String getAttr_source( )
  {
    return Attr_source;
  }

  public String[][] getAttrs( )
  {
    String[][] attrs = new String[1][2];
    attrs[0][0] = "source";
    attrs[0][1] = Attr_source;
    return attrs;
  }

  public void accept( Visitor visitor )
  {
    visitor.visitNode_promela_ast( this );
  }
}
