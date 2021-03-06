//
// Created by cyhone on 18-2-8.
//
#include <iostream>
#include <toyjvm/utilities/cmdline.h>

namespace jvm {

    static void initParser(po::options_description &opts,
                           po::positional_options_description &pos_opts,
                           CmdArgs &cmd_args)
    {
        opts.add_options()
                ("cp", po::value<std::string>(&cmd_args.class_path),
                 "<class search path of directories and zip/jar files>")

                ("classpath", po::value<std::string>(&cmd_args.class_path),
                 "<class search path of directories and zip/jar files>")

                ("help", "help info")

                ("version", "print product version and exit")

                ("class", po::value<std::string>(&cmd_args.class_name), "class name");

        pos_opts.add("class", -1);
    }

    static void printUsage(po::options_description &opts)
    {
        std::cout << opts << std::endl;
        exit(0);
    }

    static void printVersion()
    {
        std::cout << "v0.1" << std::endl;
        exit(0);
    }

    CmdArgs parseCmd(int argc, char **argv)
    {
        CmdArgs cmd_args;
        po::options_description opts;
        po::positional_options_description pos_opts;

        initParser(opts, pos_opts, cmd_args);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv)
                          .options(opts)
                          .positional(pos_opts)
                          .style(po::command_line_style::unix_style |
                                 po::command_line_style::allow_long_disguise)
                          .run(),
                  vm);
        po::notify(vm);

        if (cmd_args.class_name.empty()
            || vm.count("help")) {
            printUsage(opts);
        } else if (vm.count("version")) {
            printVersion();
        }

        return cmd_args;
    }
}

