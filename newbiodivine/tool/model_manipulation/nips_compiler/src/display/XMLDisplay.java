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
 * SAX handler which creates graphical XML tree
 */

import java.util.*;
import java.io.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.tree.*;

import javax.xml.parsers.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;

public class XMLDisplay extends DefaultHandler
{
	private boolean show = true;
    
	private Stack parents = new Stack ();
	
	private String filename;
	
	private JFrame frame = null;
	private JScrollPane pane;
 
	public XMLDisplay()
	{
		this(null);
	}
	
	public XMLDisplay(String filename, boolean show){
		this.filename = filename;
		this.show = show;
	}

	public XMLDisplay(String filename)
	{
		this.filename = filename;
	}

	public JFrame getFrame(){
		return frame;
 	}

	public JScrollPane getPane(){
		return pane;
	}
	
	public void endDocument()
	{
		frame = new JFrame ("XML Displayer" +
			 (filename != null ? " - " + filename : ""));
		JTree tree = new JTree ((DefaultMutableTreeNode) parents.pop ());
		pane = new JScrollPane (tree);
		
		expandAll (tree);
		
		/* window listener so the program will die */
		frame.addWindowListener (new WindowAdapter () {
				public void windowClosing(WindowEvent e) {
					System.exit(0);
				}
			});
		frame.setSize (300, 400);
		frame.getContentPane ().add (pane);
		if (show){
			frame.setVisible (true);
		}
	}
	
	/*
	 * As we come across non terminals, push them onto the stack
	 */
	public void startElement(String namespaceURI, String localName,
													 String qName, Attributes atts)
	{
		StringBuffer sb = new StringBuffer();
		sb.append("<html><b>" + qName + "</b>");
		for(int i = 0; i < atts.getLength(); ++i){
			sb.append(" <font color='blue'>" + atts.getQName(i) + "</font>='<font color='green'>" + atts.getValue(i) + "</font>'");
		}
		DefaultMutableTreeNode thisNode = new DefaultMutableTreeNode(sb.toString());
		if(!parents.isEmpty()) ((DefaultMutableTreeNode) parents.peek ()).add (thisNode);
		parents.push(thisNode);
	}
	
	/*
	 * As we leave a non terminal, it's parent is the node before it
	 * on the stack, so we pop it off and add it to that node
	 */
	public void endElement(String namespaceURI, String localName, String qName)
	{
		if(parents.size() > 1) parents.pop ();
	}
	
	public void characters(char[] c,int start,int length){
		int end = start + length;
		for(int i = start; i < end; ++i){
			if(!Character.isWhitespace(c[i])){
				DefaultMutableTreeNode thisNode = new DefaultMutableTreeNode(new String(c,start,length));
				((DefaultMutableTreeNode) parents.peek ()).add (thisNode);
				return;
			}
		}
	}

	public InputSource resolveEntity(String publicId, String systemId){
		if(systemId != null){
			String stripped = systemId.substring(systemId.lastIndexOf('/') + 1);
			return new InputSource(ClassLoader.getSystemResourceAsStream(stripped));
		}
		else return null;
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

	public static void main(String[] args){
		if (args.length != 1){
			System.err.println("Usage: display.XMLDisplay <file>");
			return;
		}
		try{
		  SAXParserFactory f = SAXParserFactory.newInstance();
		  f.setValidating(false);
		  SAXParser p = f.newSAXParser();
			p.parse(args[0],new XMLDisplay(args[0]));
		} catch (Exception e){
			throw new RuntimeException(e);
		}
	}

}
