/* NIPS C - New Implementation of Promela Semantics Compiler
 * display package
 * Copyright (C) 2004-2005: Peter Eisentraut <peter_e@gmx.net>
 *                          Gustavo Quiros <gustavo.quiros@rwth-aachen.de>
 *                          Michael Rohrbach <m.rohrbach00@gmx.de>
 *                          Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                          Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package display;
/*
 * NOTES
 * AST Walker which creates graphical tree
 */

import parser.Utilities;
import parser.promela.node.*;
import java.util.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.tree.*;
import parser.promela.analysis.*;

public class ASTDisplay extends DepthFirstAdapter
{
    
    private Stack parents = new Stack ();

		private String filename;
 
    public ASTDisplay()
    {
				this(null);
    }
 
		public ASTDisplay(String filename)
    {
				this.filename = filename;
    }
 
    public void outStart(Start node)
    {
				JFrame frame = new JFrame ("AST Displayer" +
																	 (filename != null ? " - " + filename : ""));
				JTree tree = new JTree ((DefaultMutableTreeNode) parents.pop ());
				JScrollPane pane = new JScrollPane (tree);
				
				expandAll (tree);
				
				/* window listener so the program will die */
				frame.addWindowListener (new WindowAdapter () {
								public void windowClosing(WindowEvent e) {
										System.exit(0);
								}
						});
				frame.setSize (300, 400);
				frame.getContentPane ().add (pane);
				frame.setVisible (true);
    }

	/*
	 * As we come across non terminals, push them onto the stack
	 */
    public void defaultIn(Node node)
    {
				DefaultMutableTreeNode thisNode = new DefaultMutableTreeNode
						(Utilities.getSimplifiedNodeName(node));
				parents.push (thisNode);
    }

	/*
	 * As we leave a non terminal, it's parent is the node before it
	 * on the stack, so we pop it off and add it to that node
	 */
    public void defaultOut(Node node)
    {
    	if (Utilities.isRelevant(node)){
			DefaultMutableTreeNode thisNode = (DefaultMutableTreeNode) parents.pop ();
			((DefaultMutableTreeNode) parents.peek ()).add (thisNode);
    	} else {
    		DefaultMutableTreeNode thisNode = (DefaultMutableTreeNode) parents.pop ();
    		while (thisNode.getChildCount() > 0){
    			((DefaultMutableTreeNode) parents.peek ()).add((DefaultMutableTreeNode) thisNode.getChildAt(0));
    		}
    	}
    }

    /*
	 * Terminals - our parent is always on the top of the stack, so we
	 * add ourselves to it
	 */
    public void defaultCase(Node node)
    {
    	if (Utilities.isRelevant((Token) node)){
			DefaultMutableTreeNode thisNode = new
				DefaultMutableTreeNode ("\"" + ((Token) node).getText () + "\", line: " + ((Token) node).getLine() + ", pos: " + ((Token) node).getPos());
			((DefaultMutableTreeNode) parents.peek ()).add (thisNode);
    	}
    }
    
    public void caseEOF(EOF node)
    {
    }

	/*
	 * we want to see the whole tree. These functions expand it for
	 * us, they are written by Christian Kaufhold and taken from the
	 * comp.lang.jave.help newsgroup
	 */
	public static void expandAll(JTree tree)
    {
        Object root = tree.getModel().getRoot();
		
        if (root != null)
            expandAll(tree, new TreePath(root));
	}
	
	
	public static void expandAll(JTree tree, TreePath path)
    {
        for (Iterator i = extremalPaths(tree.getModel(), path,
										new HashSet()).iterator();
			 i.hasNext(); )
            tree.expandPath((TreePath)i.next());
	}

	/** The "extremal paths" of the tree model's subtree starting at
        path. The extremal paths are those paths that a) are non-leaves
        and b) have only leaf children, if any. It suffices to know
        these to know all non-leaf paths in the subtree, and those are
        the ones that matter for expansion (since the concept of expan-
        sion only applies to non-leaves).
        The extremal paths of a leaves is an empty collection.
        This method uses the usual collection filling idiom, i.e.
        clear and then fill the collection that it is given, and
        for convenience return it. The extremal paths are stored
        in the order in which they appear in pre-order in the
        tree model.
    */
    public static Collection extremalPaths(TreeModel data,
										   TreePath path, 
										   Collection result)
    {
        result.clear();
		
        if (data.isLeaf(path.getLastPathComponent()))
        {
            return result; // should really be forbidden (?)
        }
        
        extremalPathsImpl(data, path, result);

        return result;
	}
	
	private static void extremalPathsImpl(TreeModel data, 
										  TreePath path,
										  Collection result)
    {
        Object node = path.getLastPathComponent();
        
        boolean hasNonLeafChildren = false;

        int count = data.getChildCount(node);
        
        for (int i = 0; i < count; i++)
            if (!data.isLeaf(data.getChild(node, i)))
                hasNonLeafChildren = true;

        if (!hasNonLeafChildren)
            result.add(path);
        else
        {
            for (int i = 0; i < count; i++)
            {
                Object child = data.getChild(node, i);
                
                if (!data.isLeaf(child))
                    extremalPathsImpl(data,
									  path.pathByAddingChild(child),
									  result);
            }
        }
	}
}



