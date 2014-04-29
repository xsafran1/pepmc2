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

import parser.promela.parser.*;
import parser.promela.node.*;
import lexer.*;

/**
 * @author Michael Rohrbach
 */
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.PushbackReader;

public class ParserMain {
	public static void main(String[] args){
		if (args.length < 1){
			System.err.println("Usage: display.ParserMain <file>");
			return;
		}
		try{
			Parser p = new Parser(new PromelaLexer(new PushbackReader(new InputStreamReader(new FileInputStream(new File(args[0]))), 1024)));
			Start tree = p.parse();
			tree.apply(new ASTDisplay(args[0]));
		} catch (Exception e){
			System.out.println(e.toString());
		}
	}
}
