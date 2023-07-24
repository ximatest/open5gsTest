export const loggerSchema = {
  type: "object",
  title: "logger",
  properties: {
    file: {
      type: "string",
      title: "Log File",
      default: "",
    },
    level: {
      type: "string",
      title: "Log Level",
      enum: ["debug", "info", "warning", "error"],
      default: "info",
    },
  },
};

export const loggerUiSchema = {
  classNames: "col-xs-12",
  file: {
    classNames: "col-xs-12",
  },
  level: {
    classNames: "col-xs-12",
  },
};

export const sbiSchema = {
  type: "object",
  properties: {
    server: {
      type: "object",
      properties: {
        no_tls: {
          type: "boolean",
          title: "No TLS",
          default: false,
        },
        no_verify: {
          type: "boolean",
          title: "No Verify",
          default: true,
        },
        cacert: {
          type: "string",
          title: "CA Cert",
          default: "",
        },
        key: {
          type: "string",
          title: "Key",
          default: "",
        },
        cert: {
          type: "string",
          title: "Cert",
          default: "",
        },
      },
    },
    client: {
      type: "object",
      properties: {
        no_tls: {
          type: "boolean",
          title: "No TLS",
          default: false,
        },
        no_verify: {
          type: "boolean",
          title: "No Verify",
          default: true,
        },
        cacert: {
          type: "string",
          title: "CA Cert",
          default: "",
        },
        key: {
          type: "string",
          title: "Key",
          default: "",
        },
        cert: {
          type: "string",
          title: "Cert",
          default: "",
        },
      },
    },
  },
};

export const sbiUiSchema = {
  classNames: "col-xs-12",
  server: {
    no_tls: {
      classNames: "col-xs-12",
    },
    no_verify: {
      classNames: "col-xs-12",
    },
    cacert: {
      classNames: "col-xs-12",
    },
    key: {
      classNames: "col-xs-12",
    },
    cert: {
      classNames: "col-xs-12",
    },
  },
  client: {
    no_tls: {
      classNames: "col-xs-12",
    },
    no_verify: {
      classNames: "col-xs-12",
    },
    cacert: {
      classNames: "col-xs-12",
    },
    key: {
      classNames: "col-xs-12",
    },
    cert: {
      classNames: "col-xs-12",
    },
  },
};

export const nrfSchema = {
  type: "object",
  properties: {
    sbi: {
      type: "array",
      title: "SBI Configuration",
      items: {
        type: "object",
        properties: {
          addr: {
                type: "array",
                items: {
                  type: "string"
                }
              },
          port: {
            type: "number",
            title: "Port",
            default: 0,
          },
        },
      },
    },
  },
};

export const nrfUiSchema = {
  classNames: "col-xs-12",
  sbi: {
    classNames: "col-xs-12",
    items: {
      addr: {
        classNames: "col-xs-12",
      },
      port: {
        classNames: "col-xs-12",
      },
    },
  },
};


export const nf_sbi_Schema = {
  type: "array",
  items: {
    type: "object",
    properties: {
      addr: {
        type: "string",
        title: "Address",
        default: "127.0.0.5"
      },
      port: {
        type: "number",
        title: "Port",
        default: 7777
      }
    }
  }
};

export const nf_sbi_UiSchema = {
  classNames: "col-xs-12",
  sbi: {
    classNames: "col-xs-12",
    items: {
      addr: {
        classNames: "col-xs-12"
      },
      port: {
        classNames: "col-xs-12"
      }
    }
  }
};

export const timeSchema = {
  type: "object",
  properties: {
    nf_instance: {
      type: "object",
      properties: {
        heartbeat: {
          type: "integer",
          default: 10
        }
      },
      required: ["heartbeat"]
    }
  }
};

export const timeUiSchema = {
  classNames: "col-xs-12",
  nf_instance: {
    classNames: "col-xs-12",
    properties: {
      heartbeat: {
        classNames: "col-xs-12"
      }
    }
  }
};

// Schema
export const icpsSchema = {
  type: "object",
  properties: {
    spsnum: {
      type: "number",
      default: 3
    },
    port: {
      type: "number",
      default: 9777
    }
  },
  required: ["spsnum", "port"]
};

// UI Schema
export const icpsUiSchema = {
  spsnum: {
    classNames: "col-xs-12"
  },
  port: {
    classNames: "col-xs-12"
  }
};

export const metricsSchema = {
  type: "array",
  items: {
    type: "object",
    properties: {
      addr: {
        type: "string",
        title: "Address",
        default: "127.0.0.5"
      },
      port: {
        type: "number",
        title: "Port",
        default: 9090
      }
    }
  }
};


export const metricsUiSchema = {
  classNames: "col-xs-12",
  metrics: {
    items: {
      addr: {
        classNames: "col-xs-12"
      },
      port: {
        classNames: "col-xs-12"
      }
    }
  }
};


export const guamiSchema = {
  type: "object",
  properties: {
    guami: {
      type: "array",
      items: {
        type: "object",
        properties: {
          plmn_id: {
            type: "object",
            properties: {
              mcc: {
                type: "integer"
              },
              mnc: {
                type: "integer"
              }
            },
            required: ["mcc", "mnc"]
          },
          amf_id: {
            type: "object",
            properties: {
              region: {
                type: "integer"
              },
              set: {
                type: "integer"
              }
            },
            required: ["region", "set"]
          }
        },
        required: ["plmn_id", "amf_id"]
      }
    }
  }
};

export const guamiUiSchema = {
  guami: {
    items: {
      plmn_id: {
        mcc: {
          classNames: "col-xs-12"
        },
        mnc: {
          classNames: "col-xs-12"
        }
      },
      amf_id: {
        region: {
          classNames: "col-xs-12"
        },
        set: {
          classNames: "col-xs-12"
        }
      }
    }
  }
};

export const taiSchema = {
  type: "object",
  properties: {
    tai: {
      type: "array",
      items: {
        type: "object",
        properties: {
          plmn_id: {
            type: "object",
            properties: {
              mcc: {
                type: "integer"
              },
              mnc: {
                type: "integer"
              }
            },
            required: ["mcc", "mnc"]
          },
          tac: {
            type: "array",
            items: {
              type: "integer"
            }
          }
        },
        required: ["plmn_id", "tac"]
      }
    }
  }
};

export const taiUiSchema = {
  tai: {
    items: {
      plmn_id: {
        mcc: {
          classNames: "col-xs-12"
        },
        mnc: {
          classNames: "col-xs-12"
        }
      },
      tac: {
        classNames: "col-xs-12"
      }
    }
  }
};

export const securitySchema = {
  type: "object",
  properties: {
    security: {
      type: "object",
      properties: {
        integrity_order: {
          type: "array",
          items: {
            type: "string"
          }
        },
        ciphering_order: {
          type: "array",
          items: {
            type: "string"
          }
        }
      },
      required: ["integrity_order", "ciphering_order"]
    }
  }
};

export const securityUiSchema = {
  security: {
    integrity_order: {
      classNames: "col-xs-12"
    },
    ciphering_order: {
      classNames: "col-xs-12"
    }
  }
};

export const networkNameSchema = {
  type: "object",
  properties: {
    network_name: {
      type: "object",
      properties: {
        full: {
          type: "string"
        }
      },
      required: ["full"]
    }
  }
};

export const networkNameUiSchema = {
  network_name: {
    full: {
      classNames: "col-xs-12"
    }
  }
};

export const amfNameSchema = {
  type: "object",
  properties: {
    amf_name: {
      type: "string"
    }
  },
  required: ["amf_name"]
};

export const amfNameUiSchema = {
  amf_name: {
    classNames: "col-xs-12"
  }
};

