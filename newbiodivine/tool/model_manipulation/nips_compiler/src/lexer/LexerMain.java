/* NIPS C - New Implementation of Promela Semantics Compiler
 * promela lexer package
 * Copyright (C) 2004-2005: Peter Eisentraut <peter_e@gmx.net>
 *                          Gustavo Quiros <gustavo.quiros@rwth-aachen.de>
 *                          Michael Rohrbach <m.rohrbach00@gmx.de>
 *                          Michael Weber <michaelw@i2.informatik.rwth-aachen.de>
 *                          Lehrstuhl fuer Informatik II, RWTH Aachen
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 */

package lexer;

import java.io.*;
import parser.promela.lexer.*;
import parser.promela.node.*;

/**
 * @author Michael Rohrbach
 */

public class LexerMain {
	public static void main(String[] args){
		if (args.length < 1){
			System.err.println("Usage: lexer.LexerMain <file>");
			return;
		}
		try {
			Lexer l = new PromelaLexer(new PushbackReader(new InputStreamReader(new FileInputStream(new File(args[0]))), 1024));
			Token token = l.next();
			while (!(token instanceof EOF)){
				System.out.println("(" + token.getLine() + ", " + token.getPos() + ", " + token.getClass().getName() + ", " + token.getText() + ")");
				token = l.next();
			}
		} catch (Exception e){
			System.out.println(e.getMessage());
			return;
		}
		return;
	}

}
