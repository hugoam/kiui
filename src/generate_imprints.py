import imp
import os

root_path = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
generator_path = os.path.join(root_path, 'sub', 'toyobj', 'src', 'Generator', 'imprint_generator.py')

imprint_generator = imp.load_source('imprint_generator', generator_path)

imprint_generator.add_module('toyobj', os.path.join(root_path, 'sub', 'toyobj', 'src', 'generator.py'))
imprint_generator.add_module('toyui', os.path.join(root_path, 'src', 'generator.py'))

imprint_generator.generate_all_modules()

