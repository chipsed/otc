#include "framework.h"
#include "headers/runtime/RuntimeHandler.h"

/**
 *
 *   ---------------- o
 * | How it's works ? |
 * o ----------------
 *
 *                           |---------------|
 *                    +++++> |  Relocations  | ======+
 * |---------|        |      |---------------|       |        |-------------------------------------------|         |---------------|       |---------------------------|
 * | Segment | =======+                              -======> | Reconstruct hotpoints with new base addr. | ======> | OWN FUNCTIONS | ====> | Call Original Entry Point |
 * |---------|        |      |---------------|       |        |-------------------------------------------|         |---------------|       |---------------------------|
 *                    +++++> |    Imports    | ======+
 *                           |---------------|
 *
 *
 *                                  +--------------------------------------------------------------+
 *                                 + ############################################################## +
 *                                + ################################################################ +
 *                               + [+----------------------------------------------------------------+] +
 *                            + # ]|[ #                      Dev - 0x000cb                         # ]|[ # +
 *                            + # ]|[ #       Telegram - t.me/array0 | Discord - 0xb00b1e5#0089    # ]|[ # +
 *                            + # ]|[ #   ------------------------------------------------------   # ]|[ # +
 *                            + # ]|[ #                   Legacy help - HoShiMin                   # ]|[ # +
 *                            + # ]|[ #                  Telegram - t.me/HoShiMin                  # ]|[ # +
 *                               + [+----------------------------------------------------------------+] +
 *                                 + ################################################################ +
 *                                  + ############################################################## +
 *                                   +--------------------------------------------------------------+
 *
 */

//Scary but necessary.
DWORD Segment::UnsafeAllocatedPointer = 0x0;
DWORD Segment::UnsafeLibraryPointer = 0x0;
SegmentFramework::VirtualFunctionCaller SegmentFramework::OriginalVirtualFunctionCaller = 0x0;

BOOL APIENTRY DllMain(HMODULE module, DWORD callReason, LPVOID lpReserved) {

    //ALL DOCS INSIDE FUNCTIONS, AND HEADERS.

    if (callReason == DLL_PROCESS_ATTACH) {

        Segment segment;
        Logger logger (Logger::LoggerType::CONSOLE);
        RuntimeHandler runtime (segment);

        PanicUtils::SetImportant (&Segment::UnsafeLibraryPointer, reinterpret_cast<DWORD> (module));

        logger.Info ("- - - - - - - - - - - - O N E T A P <-> L O A D E R - - - - - - - - - - - -");
        logger.Space ();
        logger.Info ("[RUNTIME] Extracting segment to memory....");

        runtime.ExtractSegment();
        
        logger.Info ("[RUNTIME] Segment extracted.");
        logger.Info ("[RUNTIME] Reconstructing hot-points...");

        runtime.ReconstructHotPoints();
        
        logger.Info ("[RUNTIME] Hot-points reconstructed.");
        logger.Info ("[RUNTIME] Wait until the framework complete routine work...");
        logger.Space ();

        logger.Info ("[FRAMEWORK] Filling the internal table... [Libs, Offsets] (~7-15 sec)");

        segment.GetFramework().CreateInfoTable ();

        logger.Info ("[FRAMEWORK] Table filled.");
        logger.Info ("[FRAMEWORK] Updating netvars...");

        segment.GetFramework().UpdateNetVars();

        logger.Info ("[FRAMEWORK] Netvars updated.");
        logger.Info ("[FRAMEWORK] Creating hook for internal function...");

        segment.GetFramework().CreateHook();

        logger.Info ("[FRAMEWORK] All completed.");
        logger.Space ();
        logger.Info ("[RUNTIME] Invoking OEP...");
       
        runtime.InvokeOEP();

        logger.Info ("[RUNTIME] OEP invoked.");
        logger.Space ();
            
        //Llama killed my wife for internet connecshion, pleace don't remove this. <3
        logger.Info ("To express gratitude (Bitcoin): bc1qjsjmddxegh2a0nys7czn2qztuzq8g6nwk743vg.");
        logger.Space ();
        //True.
        logger.Info ("Leaks/Cheats/Configs: https://www.yougame.biz."); 
        logger.Info ("Important: This is not an advertisement. You can find me there online 24/7. Username: 0x000cb");
        logger.Space ();

        logger.Info ("- - - - - - - - - - - - O N E T A P <-> L O A D E R - - - - - - - - - - - -");
        logger.Space ();

    }

    return TRUE;
}