####################################################################################################
# Purpose: Start or continue markdown list in stream.
####################################################################################################
def write_list(ostream, text, indent_level=0):
    for _ in range(indent_level):
        ostream.write('\t')
    ostream.write('+ ')
    ostream.write(text)
    ostream.write('\n')

####################################################################################################
# Purpose: End markdown list in stream.
####################################################################################################
def end_list(ostream):
    ostream.write('\n')

####################################################################################################
# Purpose: Write markdown paragraph to stream.
####################################################################################################
def write_paragraph(ostream, text):
    ostream.write(text)
    ostream.write('\n\n')

####################################################################################################
# Purpose: Write markdown header to stream.
####################################################################################################
def write_header(ostream, text, header_level):
    for _ in range(header_level):
        ostream.write('#')
    ostream.write(' ' + text)
    ostream.write('\n\n')
