
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <elaatomics.h>
#include <sys/mman.h>
#include "prxstub.h"
#include "rot.h"

#if defined(__USE_REMOTE_SOCKET)
    #include "sock.h"
#endif

EXTERN_C const InterfaceID EIID_IProxy;

ECode LookupClassInfo(
    /* [in] */ REMuid rclsid,
    /* [out] */ CIClassInfo **ppClassInfo);

ECode GetRemoteClassInfo(
#if !defined(__USE_REMOTE_SOCKET)
    /* [in] */ const char* connectionName,
#else
    /* [in] */ uv_tcp_t *tcp,
#endif
    /* [in] */ REMuid clsId,
    /* [out] */ CIClassInfo ** ppClassInfo);

void *GetUnalignedPtr(void *pPtr);


UInt32 g_marshalVtbl[MSH_MAX_METHODS];

#define PROXY_ENTRY_FUNC(uMethodIndex)                                         \
            ECode ProxyEntryFunc##uMethodIndex(CInterfaceProxy *pThis, ...)    \
            {                                                                  \
                va_list args;                                                  \
                ECode ec;                                                      \
                va_start(args, pThis);                                         \
                ec = CInterfaceProxy::ProxyEntry(pThis, uMethodIndex, args);   \
                va_end(args);                                                  \
                return ec;                                                     \
            }

#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__
#define FUNCTION_TABLE(seq) CAT(FUNCTION_TABLE_1 seq, _END)
#define FUNCTION_TABLE_1(x) FUNCTION(x) FUNCTION_TABLE_2
#define FUNCTION_TABLE_2(x) FUNCTION(x) FUNCTION_TABLE_1
#define FUNCTION_TABLE_1_END
#define FUNCTION_TABLE_2_END

#define FUNCTION(x) PROXY_ENTRY_FUNC(x)
FUNCTION_TABLE( (0)   (1)   (2)   (3)   (4)   (5)   (6)   (7)
                (8)   (9)   (10)  (11)  (12)  (13)  (14)  (15)
                (16)  (17)  (18)  (19)  (20)  (21)  (22)  (23)
                (24)  (25)  (26)  (27)  (28)  (29)  (30)  (31)
                (32)  (33)  (34)  (35)  (36)  (37)  (38)  (39)
                (40)  (41)  (42)  (43)  (44)  (45)  (46)  (47)
                (48)  (49)  (50)  (51)  (52)  (53)  (54)  (55)
                (56)  (57)  (58)  (59)  (60)  (61)  (62)  (63)
                (64)  (65)  (66)  (67)  (68)  (69)  (70)  (71)
                (72)  (73)  (74)  (75)  (76)  (77)  (78)  (79)
                (80)  (81)  (82)  (83)  (84)  (85)  (86)  (87)
                (88)  (89)  (90)  (91)  (92)  (93)  (94)  (95)
                (96)  (97)  (98)  (99)  (100) (101) (102) (103)
                (104) (105) (106) (107) (108) (109) (110) (111)
                (112) (113) (114) (115) (116) (117) (118) (119)
                (120) (121) (122) (123) (124) (125) (126) (127) )
#undef FUNCTION

void InitProxyEntry()
{
    g_marshalVtbl[0] = (UInt32)&CInterfaceProxy::S_Probe;
    g_marshalVtbl[1] = (UInt32)&CInterfaceProxy::S_AddRef;
    g_marshalVtbl[2] = (UInt32)&CInterfaceProxy::S_Release;
    g_marshalVtbl[3] = (UInt32)&CInterfaceProxy::S_GetInterfaceID;

    #define FUNCTION(x) g_marshalVtbl[x + 4] = (UInt32)&ProxyEntryFunc##x;
    FUNCTION_TABLE( (0)   (1)   (2)   (3)   (4)   (5)   (6)   (7)
                    (8)   (9)   (10)  (11)  (12)  (13)  (14)  (15)
                    (16)  (17)  (18)  (19)  (20)  (21)  (22)  (23)
                    (24)  (25)  (26)  (27)  (28)  (29)  (30)  (31)
                    (32)  (33)  (34)  (35)  (36)  (37)  (38)  (39)
                    (40)  (41)  (42)  (43)  (44)  (45)  (46)  (47)
                    (48)  (49)  (50)  (51)  (52)  (53)  (54)  (55)
                    (56)  (57)  (58)  (59)  (60)  (61)  (62)  (63)
                    (64)  (65)  (66)  (67)  (68)  (69)  (70)  (71)
                    (72)  (73)  (74)  (75)  (76)  (77)  (78)  (79)
                    (80)  (81)  (82)  (83)  (84)  (85)  (86)  (87)
                    (88)  (89)  (90)  (91)  (92)  (93)  (94)  (95)
                    (96)  (97)  (98)  (99)  (100) (101) (102) (103)
                    (104) (105) (106) (107) (108) (109) (110) (111)
                    (112) (113) (114) (115) (116) (117) (118) (119)
                    (120) (121) (122) (123) (124) (125) (126) (127) )
    #undef FUNCTION
}

void UninitProxyEntry()
{
}

PInterface CInterfaceProxy::S_Probe(
    /* [in] */ CInterfaceProxy *pThis,
    /* [in] */ REIID riid)
{
    return pThis->m_pOwner->Probe(riid);
}

UInt32 CInterfaceProxy::S_AddRef(
    /* [in] */ CInterfaceProxy *pThis)
{
    return pThis->m_pOwner->AddRef();
}

UInt32 CInterfaceProxy::S_Release(
    /* [in] */ CInterfaceProxy *pThis)
{
    return pThis->m_pOwner->Release();
}

ECode CInterfaceProxy::S_GetInterfaceID(
    /* [in] */ CInterfaceProxy *pThis,
    /* [in] */ IInterface *pObject,
    /* [out] */ InterfaceID *pIID)
{
    //todo: not correct.
    return pThis->m_pOwner->GetInterfaceID(pObject, pIID);
}

ECode CInterfaceProxy::BufferSize(
    /* [in] */ UInt32 uMethodIndex,
    /* [in] */ va_list vaArgs,
    /* [out] */ UInt32 *puInSize,
    /* [out] */ UInt32 *puOutSize)
{
    ECode ec;
    va_list vaArgsCopy;
    const CIMethodInfo *pMethodInfo;
    pMethodInfo = &(m_pInfo->mMethods[uMethodIndex]);

    va_copy(vaArgsCopy, vaArgs);
    ec = Proxy_ProcessMsh_BufferSize(
            pMethodInfo,
            vaArgsCopy,
            puInSize,
            puOutSize);
    va_end(vaArgsCopy);
    if (0 != *puOutSize){
        *puOutSize += sizeof(MarshalHeader);
    }

    if (SUCCEEDED(ec)) {
        *puInSize += sizeof(MarshalHeader);
    }
    return ec;
}

ECode CInterfaceProxy::MarshalIn(
    /* [in] */ UInt32 uMethodIndex,
    /* [in] */ va_list vaArgs,
    /* [in, out] */ CRemoteParcel *pParcel)
{
    ECode ec;
    va_list vaArgsCopy;
    const CIMethodInfo *pMethodInfo;
    MarshalHeader *pHeader;

    pMethodInfo = &(m_pInfo->mMethods[uMethodIndex]);

    va_copy(vaArgsCopy, vaArgs);
    ec = Proxy_ProcessMsh_In(
            pMethodInfo,
            vaArgsCopy,
            (IParcel*)pParcel);
    va_end(vaArgsCopy);

    if (SUCCEEDED(ec)) {
        pHeader = pParcel->GetMarshalHeader();
        assert(pHeader != NULL);
        pHeader->m_uMagic = MARSHAL_MAGIC;
        pHeader->m_hInterfaceIndex = m_uIndex;
        pHeader->m_hMethodIndex = uMethodIndex + 4;
    }

    return ec;
}

ECode CInterfaceProxy::UnmarshalOut(
    /* [in] */ UInt32 uMethodIndex,
    /* [out] */ CRemoteParcel *pParcel,
    /* [in] */ va_list vaArgs)
{
    MarshalHeader *pHeader = pParcel->GetMarshalHeader();
    ECode ec;
    va_list vaArgsCopy;

    if (pHeader->m_uMagic != MARSHAL_MAGIC) {
        MARSHAL_DBGOUT(MSHDBG_ERROR,
                printf("Proxy unmsh: invalid magic(%x)\n", pHeader->m_uMagic));
        return E_MARSHAL_DATA_TRANSPORT_ERROR;
    }

#if defined(_DEBUG)
    if (pHeader->m_hInterfaceIndex != (Int16)m_uIndex) {
        MARSHAL_DBGOUT(MSHDBG_ERROR,
                printf("Proxy unmsh: invalid iidx(%x)\n",
                pHeader->m_hInterfaceIndex));
        return E_MARSHAL_DATA_TRANSPORT_ERROR;
    }
    if (pHeader->m_hMethodIndex != (Int16)(uMethodIndex + 4)) {
        MARSHAL_DBGOUT(MSHDBG_ERROR, printf(
                "Proxy unmsh: invalid method(%x)\n", pHeader->m_hMethodIndex));
    }
#endif

    va_copy(vaArgsCopy, vaArgs);
    ec = Proxy_ProcessUnmsh_Out(
            &(m_pInfo->mMethods[uMethodIndex]),
            (IParcel*)pParcel,
            pHeader->m_uOutSize - sizeof(MarshalHeader),
            vaArgsCopy);
    va_end(vaArgsCopy);
    return ec;
}

UInt32 CInterfaceProxy::CountMethodArgs(
    /* [in] */ UInt32 uMethodIndex)
{
    return GET_LENGTH((m_pInfo->mMethods[uMethodIndex]).mReserved1);
}

Boolean CInterfaceProxy::MethodHasOutArgs(
    /* [in] */ UInt32 uMethodIndex)
{
    int n, cParams;
    const CIMethodInfo *pMethodInfo;
    const CIBaseType *pParams;

    pMethodInfo = &(m_pInfo->mMethods[uMethodIndex]);
    cParams = pMethodInfo->mParamNum;
    pParams = pMethodInfo->mParams;

    for (n = 0; n < cParams; n++) {
        if (BT_IS_OUT(pParams[n])) return TRUE;
    }

    return FALSE;
}

ECode CInterfaceProxy::ProxyEntry(
            /* [in] */ CInterfaceProxy *pThis,
            /* [in] */ UInt32 uMethodIndex,
            /* [in] */ va_list vaArgs)
{
    UInt32 uInSize, uOutSize;
    Int32 size = 0;
    void *pInBuffer = NULL, *pOutBuffer = NULL;
    MarshalHeader *pInHeader = NULL;
    CRemoteParcel *pInParcel = NULL, *pOutParcel = NULL;
    ECode ec;
    UInt32 cArgs;
    va_list vaArgsCopy;

#if !defined(__USE_REMOTE_SOCKET)

    DBusError err;
    DBusConnection *pconn = NULL;
    DBusMessage *pmsg = NULL;
    DBusMessage *pReply = NULL;
    DBusMessageIter args;
    DBusMessageIter subarg;

#endif

    MARSHAL_DBGOUT(MSHDBG_NORMAL, printf("iid: "));
    MARSHAL_DBGOUT(MSHDBG_NORMAL, DUMP_GUID(pThis->m_pInfo->mIID));

    // Get the stack length, not contain "this"
    cArgs = pThis->CountMethodArgs(uMethodIndex);
    MARSHAL_DBGOUT(MSHDBG_NORMAL, printf(
            "Method index(%d), args size(%d)\n", uMethodIndex + 4, cArgs * 4));

    // Calculate the package size
    //
    // NOTE:
    //  1. Alloc pOutHeader on the stack with MAX-out-size
    //  2. Assign pInHeader->m_uOutSize with MAX-out-size
    //  3. Pass the MIN-out-size to SysInvoke's last parameter
    //  4. Call Thread::ReallocBuffer in SysReply if necessary to pass back the
    //      marshaled-out data with error info
    //
    va_copy(vaArgsCopy, vaArgs);
    ec = pThis->BufferSize(uMethodIndex, vaArgsCopy, &uInSize, &uOutSize);
    va_end(vaArgsCopy);
    if (FAILED(ec)) {
        MARSHAL_DBGOUT(MSHDBG_ERROR,
                printf("Proxy BufferSize() failed, ec = %x\n", ec));
        goto ProxyExit;
    }

    MARSHAL_DBGOUT(MSHDBG_NORMAL, printf(
            "Buffer size: isize(%d), osize(%d)\n", uInSize, uOutSize));
    assert(uInSize >= sizeof(MarshalHeader));

    pInParcel = new CRemoteParcel();
    va_copy(vaArgsCopy, vaArgs);
    ec = pThis->MarshalIn(uMethodIndex, vaArgsCopy, pInParcel);
    va_end(vaArgsCopy);
    if (SUCCEEDED(ec)) {
        pInParcel->GetElementSize(&size);
        pInParcel->GetElementPayload((Handle32*)&pInBuffer);
        pInHeader = pInParcel->GetMarshalHeader();
        pInHeader->m_uInSize = size;
        pInHeader->m_uOutSize = uOutSize;
        MARSHAL_DBGOUT(MSHDBG_NORMAL, printf(
                "Before RemoteInvoke: ParcelSize(%d)\n", size));

#if defined(__USE_REMOTE_SOCKET)

        int type, len;
        char *p = NULL;

        if (sock_send_msg(pThis->m_pOwner->m_tcp,
                          METHOD_INVOKE, pInBuffer, size)) {
            ec = E_FAIL; // TODO: sould set an appropriate error code
            goto UseSocketExit;
        }

        if (sock_recv_msg(pThis->m_pOwner->m_tcp, &type, (void **)&p, &len)) {
            ec = E_FAIL; // TODO: sould set an appropriate error code
            goto UseSocketExit;
        }
        if (type != METHOD_INVOKE_REPLY) {
            ec = E_FAIL; // TODO: sould set an appropriate error code
            goto UseSocketExit;
        }

        ec = *(int32_t *)p;
        if (SUCCEEDED(ec)) {
            if (pThis->MethodHasOutArgs(uMethodIndex)) {
                pOutParcel = new CRemoteParcel((UInt32*)(p + sizeof(int32_t)));
                va_copy(vaArgsCopy, vaArgs);
                ec = pThis->UnmarshalOut(uMethodIndex, pOutParcel, vaArgsCopy);
                va_end(vaArgsCopy);
            }
        }

UseSocketExit:
        if (p) free(p);
        goto ProxyExit;

#else

        // initialiset the errors
        dbus_error_init(&err);

        // connect to the system bus and check for errors
#ifdef _MSC_VER
		pconn = dbus_bus_get_private(DBUS_BUS_SESSION, &err);
#else
    	pconn = dbus_bus_get_private(DBUS_BUS_SYSTEM, &err);
#endif
        if (dbus_error_is_set(&err)) {
            MARSHAL_DBGOUT(MSHDBG_ERROR,
                    printf("Connection Error (%s).\n", err.message));
            dbus_error_free(&err);
            ec = E_FAIL;
            goto ProxyExit;
        }

        // create a new method call and check for errors
        pmsg = dbus_message_new_method_call(
                pThis->m_pOwner->m_stubConnName, // target for the method call
                STUB_OBJECT_DBUS_OBJECT_PATH, // object to call on
                STUB_OBJECT_DBUS_INTERFACE, // interface to call on
                "Invoke");  // method name
        if (pmsg == NULL) {
            MARSHAL_DBGOUT(MSHDBG_ERROR,
                    printf("Message Null.\n"));
            ec = E_FAIL;
            goto ProxyExit;
        }

        // append arguments
        dbus_message_iter_init_append(pmsg, &args);
        dbus_message_iter_open_container(&args,
                                         DBUS_TYPE_ARRAY,
                                         DBUS_TYPE_BYTE_AS_STRING,
                                         &subarg);
        dbus_message_iter_append_fixed_array(&subarg,
                                             DBUS_TYPE_BYTE,
                                             &pInBuffer,
                                             size);
        dbus_message_iter_close_container(&args, &subarg);

        // send message and wait for a reply
        MARSHAL_DBGOUT(MSHDBG_NORMAL, printf("Request Sent.\n"));

        pReply = dbus_connection_send_with_reply_and_block(pconn, pmsg, INT_MAX, &err);
        if (dbus_error_is_set(&err)) {
            MARSHAL_DBGOUT(MSHDBG_ERROR,
                    printf("Send with reply Error (%s)\n", err.message));
            dbus_error_free(&err);
            ec = E_FAIL;
            goto ProxyExit;
        }

        // read the parameters
        if (!dbus_message_iter_init(pReply, &args)) {
            MARSHAL_DBGOUT(MSHDBG_ERROR,
                    printf("Message has no arguments.\n"));
            ec = E_FAIL;
            goto ProxyExit;
        }
        else if (DBUS_TYPE_INT32 != dbus_message_iter_get_arg_type(&args)) {
            MARSHAL_DBGOUT(MSHDBG_ERROR,
                    printf("Argument is not Int32!\n"));
            ec = E_FAIL;
            goto ProxyExit;
        }
        else {
            dbus_message_iter_get_basic(&args, &ec);
        }
        if (SUCCEEDED(ec)) {
            if (pThis->MethodHasOutArgs(uMethodIndex)) {
                if (!dbus_message_iter_next(&args)) {
                    MARSHAL_DBGOUT(MSHDBG_ERROR,
                            printf("Message has too few arguments!\n"));
                    ec = E_FAIL;
                    goto ProxyExit;
                }
                else if (DBUS_TYPE_ARRAY != dbus_message_iter_get_arg_type(&args)) {
                    MARSHAL_DBGOUT(MSHDBG_ERROR,
                            printf("Argument is not array.\n"));
                    ec = E_FAIL;
                    goto ProxyExit;
                }

                dbus_message_iter_recurse(&args, &subarg);
                dbus_message_iter_get_fixed_array(&subarg,
                                                  (void**)&pOutBuffer,
                                                  (int*)&size);

                if (pOutBuffer) {
                    pOutParcel = new CRemoteParcel((UInt32*)pOutBuffer);
                    ec = pThis->UnmarshalOut(uMethodIndex, pOutParcel, puArgs);
                }
            }
        }
        else {
            MARSHAL_DBGOUT(MSHDBG_WARNING,
                    printf("proxy RemoteInvoke() exit. ec = %x\n", ec));
        }

#endif

    }
    else {
        MARSHAL_DBGOUT(MSHDBG_ERROR,
                printf("proxy MarshalIn() failed. ec = %x\n", ec));
    }

ProxyExit:
    MARSHAL_DBGOUT(MSHDBG_NORMAL, printf("Exit proxy: ec(%x)\n", ec));

	if (pInParcel != NULL) delete pInParcel;
	if (pOutParcel != NULL) delete pOutParcel;

#if !defined(__USE_REMOTE_SOCKET)

    if (pmsg != NULL) dbus_message_unref(pmsg);
    if (pReply != NULL) dbus_message_unref(pReply);

    // free connection
    dbus_connection_close(pconn);
    dbus_connection_unref(pconn);

#endif

    return ec;
}

CObjectProxy::CObjectProxy() :
    m_pInterfaces(NULL),
    m_pICallbackConnector(NULL),
    m_cRef(1)
{}

CObjectProxy::~CObjectProxy()
{
    if (m_pInterfaces) {
        for (Int32 n = 0; n < m_cInterfaces; n++) {
            if (m_pInterfaces[n].m_pvVptr) {
		    /* Who did this?! */
                //delete [] (UInt32 *)(m_pInterfaces[n].m_pvVptr);
            }
        }
        delete [] m_pInterfaces;
    }

#if defined(__USE_REMOTE_SOCKET)

    sock_close(m_tcp);

#endif

}

static const EMuid ECLSID_XOR_CallbackSink = \
/* e724df56-e16a-4599-8edd-a97ab245d583 */
{0xe724df56,0xe16a,0x4599,{0x8e,0xdd,0xa9,0x7a,0xb2,0x45,0xd5,0x83}};

PInterface CObjectProxy::Probe(REIID riid)
{
    int n;

    if (riid == EIID_IInterface) {
        return (IInterface*)(IProxy*)this;
    }
    else if (riid == EIID_IProxy) {
        return (IProxy*)this;
    }

    if (riid == EIID_CALLBACK_CONNECTOR) {
        if (NULL == m_pICallbackConnector) {
            ClassID ezclsid;
            IInterface *pTemp = (IInterface *)&(m_pInterfaces[0].m_pvVptr);
            this->GetClassID(&ezclsid.mClsid);

            ezclsid.mClsid.mData1    ^= ECLSID_XOR_CallbackSink.mData1;
            ezclsid.mClsid.mData2    ^= ECLSID_XOR_CallbackSink.mData2;
            ezclsid.mClsid.mData3    ^= ECLSID_XOR_CallbackSink.mData3;
            ezclsid.mClsid.mData4[0] ^= ECLSID_XOR_CallbackSink.mData4[0];
            ezclsid.mClsid.mData4[1] ^= ECLSID_XOR_CallbackSink.mData4[1];
            ezclsid.mClsid.mData4[2] ^= ECLSID_XOR_CallbackSink.mData4[2];
            ezclsid.mClsid.mData4[3] ^= ECLSID_XOR_CallbackSink.mData4[3];
            ezclsid.mClsid.mData4[4] ^= ECLSID_XOR_CallbackSink.mData4[4];
            ezclsid.mClsid.mData4[5] ^= ECLSID_XOR_CallbackSink.mData4[5];
            ezclsid.mClsid.mData4[6] ^= ECLSID_XOR_CallbackSink.mData4[6];
            ezclsid.mClsid.mData4[7] ^= ECLSID_XOR_CallbackSink.mData4[7];
            ezclsid.mUunm = (char*)alloca(sizeof(char) \
                    * (strlen(((CIClassInfo*)m_pInfo)->mUunm) + 1));
            strcpy(ezclsid.mUunm, ((CIClassInfo*)m_pInfo)->mUunm);
            _CObject_AcquireClassFactory(ezclsid, RGM_SAME_DOMAIN, EIID_CALLBACK_CONNECTOR, &pTemp);
            m_pICallbackConnector = (ICallbackConnector*)pTemp;
        }
        return (IInterface*)m_pICallbackConnector;
    }

    for (n = 0; n < m_cInterfaces; n++) {
        if (riid == m_pInterfaces[n].m_pInfo->mIID) {
            break;
        }
    }
    if (n == m_cInterfaces) {
#if !defined(__USE_REMOTE_SOCKET)
        MARSHAL_DBGOUT(MSHDBG_WARNING, printf(
                "Proxy: QI failed, iid: "));
        MARSHAL_DBGOUT(MSHDBG_WARNING, DUMP_GUID(riid));
        return NULL;
#else
        // Execute a remote probe to support AOP.
        return RemoteProbe(riid);
#endif // !defined(__USE_REMOTE_SOCKET)
    }

    return (IInterface *)&(m_pInterfaces[n].m_pvVptr);
}

typedef struct ProbeRequestData {
    MarshalHeader header;
    InterfaceID iid;
} ProbeRequestData;

typedef struct ProbeReplyData {
    ECode ec;
    MarshalHeader header;
    UInt32 notNull;
    InterfacePack interfacePack;
} ProbeReplyData;

PInterface CObjectProxy::RemoteProbe(REIID riid)
{
    int type, len;
    ECode ec;
    IInterface *pObj;

    struct ProbeRequestData requestData = {
        {
            MARSHAL_MAGIC,
            0,
            0,
            sizeof(ProbeRequestData),
            sizeof(ProbeReplyData) - sizeof(ECode)
        },
        riid
    };
    struct ProbeReplyData *pReplyData;

    if (sock_send_msg(this->m_tcp,
                      METHOD_INVOKE,
                      &requestData,
                      sizeof(struct ProbeRequestData))) {
        return NULL;
    }
    if (sock_recv_msg(this->m_tcp,
                      &type,
                      (void **)&pReplyData,
                      &len)) {
        return NULL;
    }

    if (len < sizeof(ProbeReplyData) ||
            type != METHOD_INVOKE_REPLY ||
            !SUCCEEDED(pReplyData->ec)) {
        MARSHAL_DBGOUT(MSHDBG_WARNING,
                printf("proxy RemoteProbe() ec = %x\n", pReplyData->ec));
        free(pReplyData);
        return NULL;
    }
    assert(pReplyData->notNull == MSH_NOT_NULL);

    ec = StdUnmarshalInterface(UnmarshalFlag_Noncoexisting,
                               &(pReplyData->interfacePack),
                               &pObj);
    free(pReplyData);

    return SUCCEEDED(ec) ? pObj : NULL;
}

UInt32 CObjectProxy::AddRef(void)
{
    Int32 lRefs = atomic_inc(&m_cRef);

    MARSHAL_DBGOUT(MSHDBG_CREF, printf(
            "Proxy AddRef: %d\n", lRefs));
    return (UInt32)lRefs;
}

UInt32 CObjectProxy::Release(void)
{
    ECode ec;
#if !defined(__USE_REMOTE_SOCKET)

    DBusError err;
    DBusConnection *pconn = NULL;
    DBusMessage *pmsg = NULL;

#endif

    Int32 lRefs = atomic_dec(&m_cRef);

    if (lRefs == 0) {
        MARSHAL_DBGOUT(MSHDBG_NORMAL, printf(
                "Proxy destructed.\n"));

        ec = UnregisterImportObject(m_stubConnName);
        if (ec == S_FALSE) {
            return 1;// other thread hold the proxy
        }

        if (m_pICallbackConnector) {
            m_pICallbackConnector->DisconnectCallbackSink();
            delete m_pICallbackConnector;
        }

#if defined(__USE_REMOTE_SOCKET)

        if (sock_send_msg(m_tcp, METHOD_RELEASE, NULL, 0))
            goto Exit;

#else

        // Release stub's reference before destroy self.
        //
        // initialiset the errors
        dbus_error_init(&err);

        // connect to the system bus and check for errors
#ifdef _MSC_VER
		pconn = dbus_bus_get_private(DBUS_BUS_SESSION, &err);
#else
    	pconn = dbus_bus_get_private(DBUS_BUS_SYSTEM, &err);
#endif
        if (dbus_error_is_set(&err)) {
            MARSHAL_DBGOUT(MSHDBG_ERROR,
                    printf("Connection Error (%s).\n", err.message));
            dbus_error_free(&err);
            goto Exit;
        }

        // create a new method call and check for errors
        pmsg = dbus_message_new_method_call(
                m_stubConnName, // target for the method call
                STUB_OBJECT_DBUS_OBJECT_PATH, // object to call on
                STUB_OBJECT_DBUS_INTERFACE, // interface to call on
                "Release");  // method name
        if (pmsg == NULL) {
            MARSHAL_DBGOUT(MSHDBG_ERROR,
                    printf("Message Null.\n"));
            goto Exit;
        }

        // send message and wait for a reply
        MARSHAL_DBGOUT(MSHDBG_NORMAL, printf("Request Sent.\n"));

        if (dbus_connection_send(pconn, pmsg, NULL) == FALSE) {
            MARSHAL_DBGOUT(MSHDBG_ERROR,
                    printf("Send error.\n"));
        }
        dbus_connection_flush(pconn);
#endif


Exit:

#if !defined(__USE_REMOTE_SOCKET)

        if (pmsg != NULL) dbus_message_unref(pmsg);

        // free connection
        if (pconn != NULL) {
            dbus_connection_close(pconn);
            dbus_connection_unref(pconn);
        }

#endif

        delete this;

        return 0;
    }

    MARSHAL_DBGOUT(MSHDBG_CREF, printf(
            "ProxyRelease: %d\n", lRefs));

    return (UInt32)lRefs;
}

ECode CObjectProxy::GetInterfaceCount(
    /* [out] */ Int32* count) {
    assert(0);
    return NOERROR;
}

ECode CObjectProxy::GetAllInterfaceInfos(
    /* [out] */ ArrayOf<IInterfaceInfo*>* interfaceInfos) {
    assert(0);
    return NOERROR;
}

ECode CObjectProxy::GetInterfaceID(
    /* [in] */ IInterface *pObject,
    /* [out] */ InterfaceID *pIID)
{
    if (NULL == pIID) return E_INVALID_ARGUMENT;

    if (pObject == (IInterface *)(IProxy *)this) {
        *pIID = EIID_IProxy;
    }
    else {
        return E_INVALID_ARGUMENT;
    }
    return NOERROR;
}

ECode CObjectProxy::GetInterface(
    /* [in] */ UInt32 uIndex,
    /* [out] */ IInterface **ppObj)
{
    assert(ppObj != NULL);

    if (uIndex < (UInt32)m_cInterfaces) {
        *ppObj = (IInterface *)&(m_pInterfaces[uIndex].m_pvVptr);
        this->AddRef();
        return NOERROR;
    }
    MARSHAL_DBGOUT(MSHDBG_WARNING, printf(
            "Proxy: IndexQI failed - idx(%d), cInterfaces(%d)\n",
            uIndex, m_cInterfaces));

    return E_NO_INTERFACE;
}

ECode CObjectProxy::GetInterfaceIndex(
     /* [in] */ IInterface *pObj,
     /* [out] */ UInt32* pIndex)
{
    assert(pIndex != NULL);

    Int32 Index = 0;
    while (Index < m_cInterfaces) {
        if ((void*)pObj == &(m_pInterfaces[Index].m_pvVptr)) {
            *pIndex = Index;
            return NOERROR;
        }
        Index++;
    }
    return E_NO_INTERFACE;
}

ECode CObjectProxy::GetClassID(
    /* [out] */ EMuid *pClsid)
{
    assert(pClsid != NULL);

    *pClsid = ((CIClassInfo*)m_pInfo)->mCLSID;
    return NOERROR;
}

ECode CObjectProxy::GetClassInfo(
    /* [out] */ CIClassInfo **ppClassInfo)
{
    assert(ppClassInfo != NULL);

    *ppClassInfo = m_pInfo;
    return NOERROR;
}

ECode CObjectProxy::LinkToDeath(
    /* [in] */ IProxyDeathRecipient* recipient,
    /* [in] */ Int32 flags)
{
    assert(0);

    return NOERROR;
}

ECode CObjectProxy::UnlinkToDeath(
    /* [in] */ IProxyDeathRecipient* recipient,
    /* [in] */ Int32 flags,
    /* [out] */ Boolean* result)
{
    assert(0);

    return NOERROR;
}

ECode CObjectProxy::IsStubAlive(
    /* [out] */ Boolean* result) {
    assert(0);

    return NOERROR;
}

ECode CObjectProxy::S_CreateObject(
    /* [in] */ REMuid rclsid,
    /* [in] */ const char* stubConnName,
    /* [out] */ IProxy **ppIProxy)
{
    CObjectProxy *pProxy;
    CInterfaceProxy *pInterfaces;
    Int32 n;
    ECode ec;

    if (ppIProxy == NULL) return E_INVALID_ARGUMENT;

    pProxy = new CObjectProxy();
    if (!pProxy) {
        MARSHAL_DBGOUT(MSHDBG_ERROR,
                printf("Create proxy object: out of memory.\n"));
        return E_OUT_OF_MEMORY;
    }

    pProxy->m_stubConnName = stubConnName;

#if defined(__USE_REMOTE_SOCKET)

    char ip[32];
    int port;

    sscanf(stubConnName, "%[^:]:%d", ip, &port);

    pProxy->m_stubIP = ip;
    pProxy->m_stubPort = port;

    if (sock_connect(&pProxy->m_tcp, ip, port)) {
        ec = E_FAIL;
        goto ErrorExit;
    }

#endif

    ec = LookupClassInfo(rclsid, &(pProxy->m_pInfo));
    if (FAILED(ec)) {
        ec = GetRemoteClassInfo(pProxy->m_tcp,
                                 rclsid,
                                 &pProxy->m_pInfo);
        if (FAILED(ec)) goto ErrorExit;
    }

    pProxy->m_cInterfaces = ((CIClassInfo*)(pProxy->m_pInfo))->mInterfaceNum;
    pInterfaces = new CInterfaceProxy[pProxy->m_cInterfaces];
    if (!pInterfaces) {
        MARSHAL_DBGOUT(MSHDBG_ERROR,
                printf("Create proxy interfaces: out of memory.\n"));
        ec = E_OUT_OF_MEMORY;
        goto ErrorExit;
    }
    pProxy->m_pInterfaces = pInterfaces;
    memset(pInterfaces, 0, sizeof(CInterfaceProxy) * pProxy->m_cInterfaces);
    for (n = 0; n < pProxy->m_cInterfaces; n++) {
        pInterfaces[n].m_uIndex = n;
        pInterfaces[n].m_pOwner = pProxy;
        CIInterfaceInfo *pInterfaceInfo =
            (CIInterfaceInfo *)GetUnalignedPtr(
                    pProxy->m_pInfo->mInterfaces + n);
        pInterfaces[n].m_pInfo = pInterfaceInfo;
        pInterfaces[n].m_pvVptr = g_marshalVtbl;
    }

    ec = RegisterImportObject(pProxy->m_stubConnName, (IProxy*)pProxy);
    if (FAILED(ec)) {
        MARSHAL_DBGOUT(MSHDBG_ERROR, printf(
                "Create proxy: register import object failed, ec(%x)\n",
                ec));
        goto ErrorExit;
    }

    *ppIProxy = (IProxy*)pProxy;

    return NOERROR;

ErrorExit:

#if defined(__USE_REMOTE_SOCKET)

    if (pProxy->m_tcp != 0)
        sock_close(pProxy->m_tcp);

#endif

    delete pProxy;
    return ec;
}
