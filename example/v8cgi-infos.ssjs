/**
 * HTML rendering of the global object
 *
 * WARNING: For debugging purpose only: this is not secure at all ! You should never let your users access to this file.
 */
response.write( HTML.dump(global) );
