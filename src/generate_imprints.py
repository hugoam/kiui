import imp
import os

dir_path = os.path.dirname(os.path.realpath(__file__))

imp.load_source('toyobj_imprints', '../sub/toyobj/src/generate_imprints.py')

from toyobj_imprints import root, toyobj
from imprint_generator import Module, generate_module
                
toyui = Module(root, 'mk', 'mk', 'Ui', [toyobj], dir_path)
            
generate_module(toyui)
