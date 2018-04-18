
# Build CAR Compiler

In general, you will not use it. It will be used after you modified the source code of the CAR tools.

1. Enter the build environment:

   * Ubuntu_32bit
     ```
     $ source ~/Elastos.RT/Setup/SetEnv.sh devtools_32
     ```
     or
     ```
     $ source ~/Elastos.RT/Setup/SetEnv.sh
     ```
     and then choose the index number of the "devtools_32" item from the numbered list

   * Ubuntu_64bit
     ```
     $ source ~/Elastos.RT/Setup/SetEnv.sh devtools_64
     ```
     or
     ```
     $ source ~/Elastos.RT/Setup/SetEnv.sh
     ```
     and then choose the index number of the "devtools_64" item from the numbered list

   * linux_devtools_64: 64 bits linux tools for the new cmake build environment
     ```
     $ source ~/Elastos.RT/Setup/SetEnv.sh linux_devtools_64
     ```
     or
     ```
     $ source ~/Elastos.RT/Setup/SetEnv.sh
     ```
     and then choose the index number of the "linux_devtools_64" item from the numbered list

   * linux_devtools_32: 32 bits linux tools for the new cmake build environment
     ```
     $ source ~/Elastos.RT/Setup/SetEnv.sh linux_devtools_32
     ```
     or
     ```
     $ source ~/Elastos.RT/Setup/SetEnv.sh
     ```
     and then choose the index number of the "linux_devtools_32" item from the numbered list

   * mac_devtools_64: mac tools for the new cmake build environment
     ```
     $ source ~/Elastos.RT/Setup/SetEnv.sh mac_devtools_64
     ```
     or
     ```
     $ source ~/Elastos.RT/Setup/SetEnv.sh
     ```
     and then choose the index number of the "mac_devtools_64" item from the numbered list

   * mac_devtools_32: mac tools for the new cmake build environment
     ```
     $ source ~/Elastos.RT/Setup/SetEnv.sh mac_devtools_32
     ```
     or
     ```
     $ source ~/Elastos.RT/Setup/SetEnv.sh
     ```
     and then choose the index number of the "mac_devtools_32" item from the numbered list

2. Build CAR tools

   Build release version of CAR compiler

   ```
   ~/Elastos.RT/Sources$ rls
   ~/Elastos.RT/Sources$ emake
   ~/Elastos.RT/Sources$ pd @
   ```

3. Deploy the new CAR tools

   Copy your build result to ~/Elastos.RT/Build/Tools

   * Ubuntu_32bit
     ```
     cp CInfoReader Cls2C carc carcode lubc lube libz.so ~/Elastos.RT/Build/Tools_32/
     ```

   * Ubuntu_64bit
     ```
     cp CInfoReader Cls2C carc carcode lubc lube libz.so ~/Elastos.RT/Build/Tools_64/
     ```

   * linux_devtools_64
     ```
     cp CInfoReader Cls2C carc carcode lubc lube ~/Elastos.RT/Build/Tools/64/linux/
     cp lube.lbo systypes.cls ~/Elastos.RT/Build/Tools/64/
     ```

   * linux_devtools_32
     ```
     cp CInfoReader Cls2C carc carcode lubc lube ~/Elastos.RT/Build/Tools/32/linux/
     cp lube.lbo systypes.cls ~/Elastos.RT/Build/Tools/32/
     ```

   * mac_devtools_64
     ```
     cp Cls2C carc carcode lubc lube ~/Elastos.RT/Build/Tools/64/mac/
     cp lube.lbo systypes.cls ~/Elastos.RT/Build/Tools/64/
     ```

   * mac_devtools_32
     ```
     cp Cls2C carc carcode lubc lube ~/Elastos.RT/Build/Tools/32/mac/
     cp lube.lbo systypes.cls ~/Elastos.RT/Build/Tools/32/
     ```

4. Change between release version and debug version
   ```
   rls    #It is an alias of  --> chv rls
   dbg    #It is an alias of  --> chv dbg
   ```