from distutils.core import setup, Extension

sanity_hash_module = Extension('sanity_hash',
                                 sources = ['sanitymodule.c',
                                            'sanity.c',
                                            'sha3/blake.c',
                                            'sha3/groestl.c',
                                            'sha3/jh.c',
                                            'sha3/keccak.c',
                                            'sha3/skein.c',
                                            'sha3/luffa.c',
                                            'sha3/simd.c'],
                               include_dirs=['.', './sha3'])

setup (name = 'sanity_hash',
       version = '1.3.2',
       description = 'Binding for Sanity proof of work hashing.',
       ext_modules = [sanity_hash_module])
